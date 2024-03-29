#include "ray_tracer.h"

// Constructor
RayTracer::RayTracer(int width, int height, int fov, int numSamples, int numThreads, double rayStepSize, int maxRaySteps, int maxRayDepth, double rayTol, int maxIter) {
	this->cam = Camera(width, height, fov);
	this->numSamples = numSamples;
	this->numThreads = numThreads;
	this->rayStepSize = rayStepSize;
	this->maxRaySteps = maxRaySteps;
	this->maxRayDepth = maxRayDepth;
	this->rayTol = rayTol;
	this->maxIter = maxIter;
	this->objs = objs;
	this->lights = lights;
	this->pixels = new Vect*[height];
	for (int i = 0; i < height; i++)
		this->pixels[i] = new Vect[width];
}
// Destructor
RayTracer::~RayTracer() {
	// Delete objects
	for (int i = 0; i < objs.size(); ++i)
		delete objs.at(i);
	// Delete lights
	for (int i = 0; i < lights.size(); ++i)
		delete lights.at(i);
	// Delete image array
	for (int i = 0; i < cam.height; i++)
		delete[] this->pixels[i];
	delete[] this->pixels;
}

// Renders an image from objects and lights
Vect **RayTracer::render() {
	// Calculate constants
	double span = 2.0 * tan(PI * cam.fov / 360.0);
	double ratio = span / MAX(cam.width, cam.height);
	double sampleSize = 1.0 / numSamples;
	
	// Create array of threads
	std::thread threads[numThreads];
	int rowsPerThread = cam.height / numThreads;

	// Start timer
	time_t start = time(NULL);

	// Create threads
	for (int i = 0; i < numThreads; ++i) // Screen height resolution
		threads[i] = std::thread(renderThread, this, i, rowsPerThread, ratio, sampleSize);
	printf("Rendering...\n");
	// Wait for each thread to finish and join it
	for (int i = 0; i < numThreads; ++i)
		threads[i].join();

	// Print results
	time_t seconds = time(NULL) - start;
	time_t minutes = seconds / 60L; seconds %= 60L;
	time_t hours   = minutes / 60L; minutes %= 60L;
	printf("Render time: %02ld:%02ld:%02lds\n", hours, minutes, seconds);

	return pixels;
}

// Renders multiple rows of pixels in each thread. The function is static because a non-static function
// can't be passed to a thread. To bypass this, it takes the object as an argument
void RayTracer::renderThread(RayTracer *rt, int index, int rowsPerThread, double ratio, double sampleSize) {
	// Calculate which rows to render in this thread
	int minRow = index * rowsPerThread;
	int maxRow;
	if (index <= rt->numThreads - 1)
		maxRow = minRow + rowsPerThread - 1;
	else // In case height isn't divisible by number of threads
		maxRow = rt->cam.height - 1;
	// Render selected rows
	for (int row = minRow; row <= maxRow; ++row) {
		for (int col = 0; col < rt->cam.width; ++col) { // Screen width resolution
			Vect color = Vect(0.0, 0.0, 0.0);
			for (int dy = 0; dy < rt->numSamples; ++dy) { // Pixel height samples
				for (int dx = 0; dx < rt->numSamples; ++dx) { // Pixel width samples
					double x = ratio * ((col + (0.5+dx) * sampleSize) - rt->cam.width*0.5);
					double y = ratio * (-(row + (0.5+dy) * sampleSize) + rt->cam.height*0.5);
					// Get ray through the selected sample of the selected pixel
					Vect rayDir = rt->cam.vx*x + rt->cam.vy*y + rt->cam.dir;
					rayDir.normalize();
					Ray ray = Ray(rt->cam.pos, rayDir);
					// Trace ray
					Vect sampleColor = rt->trace(ray, 0, 0, NULL);
					color += sampleColor;
				}
			}
			rt->pixels[row][col] = color / (rt->numSamples * rt->numSamples); // Store average color from all samples
		}
	}
}

// Traces ray through space and finds collisions with objects, then recursively
// sends out a reflection ray, a refraction ray and a shadow ray.
Vect RayTracer::trace(Ray& ray, int depth, int currentSteps, int *signsPrev) {
	Vect color = Vect(0.0, 0.0, 0.0); // Default color
	// Base case
	if (depth > maxRayDepth)
		return color;

	// Get function signs at the origin unless already given
	int signs[objs.size()]; // + => 1, - => 0
	for (int i = 0; i < objs.size(); ++i) {
		if (signsPrev == NULL)
			signs[i] = objs.at(i)->f(ray.origin) >= 0; // TODO: If == 0
		else
			signs[i] = signsPrev[i];
	}

	double t = 0.0;
	for (int step = currentSteps + 1; step < maxRaySteps; ++step) {
		t += rayStepSize;
		Vect point = ray * t;
		// If multiple collisions, get the closest one
		int iObj = -1;
		for (int i = 0; i < objs.size(); ++i) {
			int sign = objs.at(i)->f(point) >= 0;
			if (sign != signs[i]) {
				// Calculate collision with object
				double t0 = t - 0.5 * rayStepSize;
				double tn = newton(objs.at(i), ray, t0, rayTol, maxIter);
				if (iObj == -1 || tn < t) {
					iObj = i;
					t = tn;
				}
			}
		}
		// Nearest collision found
		if (iObj != -1) {
			point = ray * t; // Point of collision
			int sign = signs[iObj]; // Tells us whether the ray came from the outside or from the inside of the object
			Vect normal = objs.at(iObj)->grad(point).normalize();
			if (sign == 0) // If we're inside of the object invert the normal vector
				normal *= -1.0;
			double reflection = objs.at(iObj)->mat.reflection;
			double transparency = objs.at(iObj)->mat.transparency;

			// Diffuse
			if (reflection < 1.0) {
				Vect light = traceShadow(point, normal, signs);
				Vect diffuseColor = light * objs.at(iObj)->mat.color;
				// Set diffuse color
				color = diffuseColor;
			}
			// Reflection
			Vect reflectionColor;
			if (reflection > 0.0) {
				double cosPhi = -1.0 * ray.dir.dot(normal);
				Vect reflectionDir = ray.dir + normal * cosPhi * 2.0; // Already normalized
				Ray reflectionRay = Ray(point, reflectionDir);
				reflectionColor = trace(reflectionRay, depth+1, step, signs);
				// Set reflection color
				color = color * (1-reflection) + reflectionColor * reflection;
			}
			// Refraction
			if (transparency > 0.0) {
				double refractiveIndex = objs.at(iObj)->mat.refractiveIndex;
				double n1 = 1.0, n2 = 1.0; // We assume the refractive index of air is 1
				if (sign == 1) // Positive, ray is coming from the outside of the object
					n2 = refractiveIndex;
				else // Negative, ray is coming from the inside of the object
					n1 = refractiveIndex;
				// Angle of incidence
				double cosPhi1 = -1.0 * ray.dir.dot(normal);
				double sinPhi1 = sqrt(1 - cosPhi1*cosPhi1);

				Vect refractionColor; // Outside of if because it can be used in refraction
				if (sinPhi1 > n2 / n1) { // Total internal reflection
					if (reflection > 0.0) { // Reflection already calculated
						refractionColor = reflectionColor.copy();
					} else { // Reflection not calculated yet
						Vect tiReflectionDir = ray.dir + normal * cosPhi1 * 2.0; // Already normalized
						Ray tiReflectionRay = Ray(point, tiReflectionDir);
						refractionColor = trace(tiReflectionRay, depth+1, step, signs);
					}
				} else { // Refraction
					// Angle of refraction
					double sinPhi2 = sinPhi1 * (n1 / n2);
					double cosPhi2 = sqrt(1 - sinPhi2*sinPhi2);

					Vect refractionDir = (ray.dir + normal*cosPhi1) * (n1 / n2) - normal * cosPhi2;
					Ray refractionRay = Ray(point, refractionDir);
					signs[iObj] = 1 - sign;
					refractionColor = trace(refractionRay, depth+1, step, signs);
					signs[iObj] = sign;
				}
				// Set refraction color
				color = color * (1-transparency) + refractionColor * transparency;
			}

			return color;
		}
	}
	return color;
}

// Traces shadow rays from origin point to all light sources and returns the total illumination
Vect RayTracer::traceShadow(Vect& origin, Vect& normal, int *signsPrev) {
	// Copy previous signs
	int signs[objs.size()];
	for (int i = 0; i < objs.size(); ++i)
		signs[i] = signsPrev[i];

	Vect illum = Vect(0.0); // Default illumination
	for (int j = 0; j < lights.size(); ++j) {
		Vect shadowRayDir = lights.at(j)->pos - origin;
		double tMax = shadowRayDir.length();
		shadowRayDir.normalize();
		Ray shadowRay = Ray(origin, shadowRayDir);
		// Trace shadow ray
		double t = 0.0;
		double intensity = 1.0;
		while (t < tMax) {
			t += rayStepSize;
			if (t > tMax) // Last point should be on the light itself
				t = tMax;
			Vect point = shadowRay * t;
			for (int i = 0; i < objs.size(); ++i) {
				int sign = objs.at(i)->f(point) >= 0;
				if (sign != signs[i]) { // Shadow ray collision with object
					intensity *= objs.at(i)->mat.transparency;
					if (intensity == 0)
						break;
					signs[i] = sign; // Why can't this line be before break?
				}
			}
			if (intensity == 0) // If light not visible anymore
				break;
		}
		if (intensity > 0.0) { // Calculate light angle and apply intensity
			double cosPhi = shadowRay.dir.dot(normal);
			if (cosPhi < 0.0)
				cosPhi = 0.0;
			Vect currentIllum = lights.at(j)->brightness * cosPhi * intensity;
			illum.addBalanced(currentIllum); // TODO: Fix
		}
	}
	return illum;
}

// Finds the intersetion of the ray with the object using Newton's method
double RayTracer::newton(Object* obj, Ray& ray, double t, double tol, int maxIter) {
	double t0 = t;
	for (int i = 0; i < maxIter; ++i) {
		Vect point = ray * t0;
		double g = obj->f(point); // We want to find the zero of this function with regard to t
		//double dg = ray.dir.x * obj->dfx(point) + ray.dir.y * obj->dfy(point) + ray.dir.z * obj->dfz(point);
		double dg = obj->grad(point).dot(ray.dir); // Equivalent
		t = t0 - g / dg;
		if (ABS(g) < tol)
			break;
		t0 = t;
	}
	return t;
}

// Sets camera position
void RayTracer::setCamPos(double x, double y, double z) {
	cam.pos.x = x;
	cam.pos.y = y;
	cam.pos.z = z;
}
// Sets camera direction towards the given point
void RayTracer::setCamDir(double x, double y, double z) {
	Vect pt = Vect(x, y, z);
	if (cam.pos.equals(pt))
		return;
	Vect dir = (pt - cam.pos).normalize();
	cam.dir = dir;
}

// Add an object to the scene
void RayTracer::addObject(Object* obj) {
	this->objs.push_back(obj);
}
// Add a light to the scene
void RayTracer::addLight(Light* light) {
	this->lights.push_back(light);
}
