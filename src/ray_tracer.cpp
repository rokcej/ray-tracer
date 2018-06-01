#include "ray_tracer.h"

RayTracer::RayTracer(int width, int height, int fov, int samples, std::vector<Object*>& objs, std::vector<Light*>& lights) {
	this->cam = Camera(width, height, fov);
	this->samples = samples;
	this->objs = objs;
	this->lights = lights;
	this->pixels = new Vect*[height];
	for (int i = 0; i < height; i++)
		this->pixels[i] = new Vect[width];
}
RayTracer::~RayTracer() {
	for (int i = 0; i < cam.height; i++)
		delete[] this->pixels[i];
	delete[] this->pixels;
}

Vect **RayTracer::render() {
	double span = 2.0 * tan(PI * cam.fov / 360.0);
	double ratio = span / MAX(cam.width, cam.height);
	double sampleSize = 1.0 / samples;

	for (int row = 0; row < cam.height; ++row) { // Screen height resolution
		for (int col = 0; col < cam.width; ++col) { // Screen width resolution
			Vect color = Vect(0.0, 0.0, 0.0);
			for (int dy = 0; dy < samples; ++dy) { // Pixel height samples
				for (int dx = 0; dx < samples; ++dx) { // Pixel width samples
					double x = ratio * ((col + (0.5+dx) * sampleSize) - cam.width*0.5);
					double y = ratio * (-(row + (0.5+dy) * sampleSize) + cam.height*0.5);

					Vect rayDir = cam.vx*x + cam.vy*y + cam.dir;
					rayDir.normalize();

					Ray ray = Ray(cam.pos, rayDir);
					Vect sampleColor = trace(ray, 0, NULL);
					color += sampleColor;
				}
			}
			pixels[row][col] = color / (samples * samples); // Store average color
		}
	}
	return pixels;
}

Vect RayTracer::trace(Ray& ray, int depth, int *signsPrev) {
	Vect color = Vect(0.0, 0.0, 0.0); // Default color
	// Base case
	if (depth > MAX_RAY_DEPTH)
		return color;

	// Get function signs at the origin unless already given
	int signs[objs.size()];
	for (int i = 0; i < objs.size(); ++i) {
		if (signsPrev == NULL)
			signs[i] = objs.at(i)->f(ray.origin) >= 0; // TODO: If == 0
		else
			signs[i] = signsPrev[i];
	}

	double t = 0.0;
	for (int step = 1; step < MAX_RAY_STEPS; ++step) {
		t += RAY_STEP_SIZE;
		Vect point = ray * t;
		// If multiple collisions, get the closest one
		int iObj = -1;
		for (int i = 0; i < objs.size(); ++i) {
			int sign = objs.at(i)->f(point) >= 0;
			if (sign != signs[i]) {
				// Calculate collision with object
				double t0 = t - 0.5 * RAY_STEP_SIZE;
				double tn = newton(objs.at(i), ray, t0, RAY_TOL, MAX_ITER);
				if (iObj == -1 || tn < t) {
					iObj = i;
					t = tn;
				}
			}
		}
		// Nearest collision found
		if (iObj != -1) {
			point = ray * t;
			Vect normal = objs.at(iObj)->grad(point).normalize();
			double reflection = objs.at(iObj)->mat.reflection;
			double transparency = objs.at(iObj)->mat.transparency;

			// Diffuse
			Vect light = traceShadow(point, normal, signs);
			Vect diffuseColor = light * objs.at(iObj)->mat.color;

			color = diffuseColor;

			// Reflection
			if (reflection > 0.0) {
				Vect reflectionDir = ray.dir - normal * ray.dir.dot(normal) * 2.0; // Already normalized
				Ray reflectionRay = Ray(point, reflectionDir);
				Vect reflectionColor = trace(reflectionRay, depth+1, signs);

				color = color * (1-reflection) + reflectionColor * reflection;
			}
			//Transparency
			if (transparency > 0.0) {
				Ray transparencyRay = Ray(point, ray.dir);
				signs[iObj] = 1 - signs[iObj];
				Vect transparencyColor = trace(transparencyRay, depth+1, signs);
				signs[iObj] = 1 - signs[iObj];
				
				color = color * (1-transparency) + transparencyColor * transparency;
			}

			return color;
		}
	}
	return color;
}

// Traces shadow rays from origin to light sources
Vect RayTracer::traceShadow(Vect& origin, Vect& normal, int *signsPrev) {
	// Copy previous signs
	int signs[objs.size()];
	for (int i = 0; i < objs.size(); ++i)
			signs[i] = signsPrev[i];

	Vect illum = Vect(0.1);
	for (int j = 0; j < lights.size(); ++j) {
		Vect rayDir = lights.at(j)->pos - origin;
		double tMax = rayDir.length();
		rayDir.normalize();
		Ray ray = Ray(origin, rayDir);
		// Trace shadow ray
		double t = 0.0;
		double intensity = 1.0;
		while (t < tMax) {
			t += RAY_STEP_SIZE;
			if (t > tMax) // Last point should be on the light itself
				t = tMax;
			Vect point = ray * t;
			for (int i = 0; i < objs.size(); ++i) {
				int sign = objs.at(i)->f(point) >= 0;
				if (sign != signs[i]) {
					intensity *= objs.at(i)->mat.transparency;
					break;
				}
			}
			if (intensity == 0)
				break;
		}
		if (intensity > 0.0) {
			double cosAngle = normal.dot(ray.dir);
			//printf("%f, %f, %f\n", cosAngle, normal.length(), ray.dir.length());
			if (cosAngle < 0.0)
				cosAngle = 0.0;
			double minLum = 0.00; // TODO: Make this a material attribute
			Vect currentIllum = lights.at(j)->brightness * (cosAngle * (1-minLum) + minLum);
			illum.addBalanced(currentIllum); // TODO: Fix
		}
	}
	return illum;
}

double RayTracer::newton(Object* obj, Ray& ray, double t, double tol, int max_iter) {
	double t0 = t;
	for (int i = 0; i < max_iter; ++i) {
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
