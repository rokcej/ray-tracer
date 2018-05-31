#include "ray_tracer.h"

RayTracer::RayTracer(std::vector<Object*>& objs, std::vector<Light*>& lights) {
	this->cam = Camera();
	this->objs = objs;
	this->lights = lights;
}

Pixel RayTracer::render(int width, int height, int col, int row) {
	double span = 2.0 * tan(PI * cam.fov / 360.0);
	double ratio = span / MAX(width, height);
	double x = ratio * ((col + 0.5) - width/2.0);
	double y = ratio * (-(row + 0.5) + height/2.0);

	Vect rayDir = cam.vx*x + cam.vy*y + cam.dir;
	rayDir.normalize();

	Ray ray = Ray(cam.pos, rayDir);
	return trace(ray, 0);
}

Pixel RayTracer::trace(Ray& ray, int depth) {
	// Get function signs at the origin
	int n = objs.size();
	int signs[n];
	for (int i = 0; i < n; ++i)
		signs[i] = objs.at(i)->f(ray.origin) >= 0; // TODO: If == 0

	double t = 0.0;
	for (int step = 1; step < MAX_STEPS; ++step) {
		t += STEP_SIZE;
		Vect tPoint = ray * t;
		// If multiple collisions, get the closest one
		int iObj = -1;
		for (int i = 0; i < n; ++i) {
			int sign = objs.at(i)->f(tPoint) >= 0;
			if (sign != signs[i]) {
				// Calculate collision with object
				double t0 = t - 0.5 * STEP_SIZE;
				double tn = newton(objs.at(i), ray, t0, TOL, MAX_ITER);
				if (iObj == -1 || tn < t) {
					iObj = i;
					t = tn;
				}
			}
		}
		// Nearest collision found
		if (iObj != -1) {
			tPoint = ray * t;
			// Illumination
			double illumination = 0.4;
			for (int j = 0; j < lights.size(); ++j) {
				Vect shadowRayDir = lights.at(j)->pos - tPoint;
				double sMax = shadowRayDir.length();
				shadowRayDir.normalize();
				Ray shadowRay = Ray(tPoint, shadowRayDir);
				// Trace shadow ray
				double s = 0.0;
				int shadow = 0;
				while (s < sMax) {
					s += STEP_SIZE;
					if (s > sMax) // Last point should be on the light itself
						s = sMax;
					Vect sPoint = shadowRay * s;
					for (int i = 0; i < n; ++i) {
						int sign = objs.at(i)->f(sPoint) >= 0;
						if (sign != signs[i]) {
							shadow = 1;
							break;
						}
					}
					if (shadow)
						break;
				}
				if (!shadow)
					illumination += lights.at(j)->brightness;

			}
			return (Pixel) { illumination, illumination, illumination };
		}
	}
	return (Pixel) { 0.0, 0.0, 0.0 };
}

double RayTracer::newton(Object* obj, Ray& ray, double t, double tol, int max_iter) {
	double t0 = t;
	for (int i = 0; i < max_iter; ++i) {
		Vect point = ray * t0;
		t = t0 - obj->f(point) / (ray.dir.x * obj->dfx(point) + ray.dir.y * obj->dfy(point) + ray.dir.z * obj->dfz(point));
		if (ABS(t - t0) < tol)
			break;
		t0 = t;
	}
	return t;
}
