#include "ray_tracer.h"

RayTracer::RayTracer(std::vector<Object*>& objs, std::vector<Light*>& lights) {
	this->cam = Camera();
	this->objs = objs;
	this->lights = lights;
}

Vect RayTracer::render(int width, int height, int col, int row) {
	double span = 2.0 * tan(PI * cam.fov / 360.0);
	double ratio = span / MAX(width, height);
	double x = ratio * ((col + 0.5) - width/2.0);
	double y = ratio * (-(row + 0.5) + height/2.0);

	Vect rayDir = cam.vx*x + cam.vy*y + cam.dir;
	rayDir.normalize();

	Ray ray = Ray(cam.pos, rayDir);
	return trace(ray, 0);
}

Vect RayTracer::trace(Ray& ray, int depth) {
	// Get function signs at the origin
	int signs[objs.size()];
	for (int i = 0; i < objs.size(); ++i)
		signs[i] = objs.at(i)->f(ray.origin) >= 0; // TODO: If == 0

	double t = 0.0;
	for (int step = 1; step < MAX_STEPS; ++step) {
		t += STEP_SIZE;
		Vect point = ray * t;
		// If multiple collisions, get the closest one
		int iObj = -1;
		for (int i = 0; i < objs.size(); ++i) {
			int sign = objs.at(i)->f(point) >= 0;
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
			point = ray * t;
			Vect color = Vect(1.0, 1.0, 1.0);
			color *= traceShadow(point, signs);
			return color;
		}
	}
	return Vect(0.0, 0.0, 0.0);
}

// Traces shadow rays from origin to light sources
Vect RayTracer::traceShadow(Vect origin, int *signs) {
	Vect illum = Vect(0.5);
	for (int j = 0; j < lights.size(); ++j) {
		Vect rayDir = lights.at(j)->pos - origin;
		double tMax = rayDir.length();
		rayDir.normalize();
		Ray ray = Ray(origin, rayDir);
		// Trace shadow ray
		double t = 0.0;
		int shadow = 0;
		while (t < tMax) {
			t += STEP_SIZE;
			if (t > tMax) // Last point should be on the light itself
				t = tMax;
			Vect point = ray * t;
			for (int i = 0; i < objs.size(); ++i) {
				int sign = objs.at(i)->f(point) >= 0;
				if (sign != signs[i]) {
					shadow = 1;
					break;
				}
			}
			if (shadow)
				break;
		}
		if (!shadow)
			illum += lights.at(j)->brightness; // TODO: Fix
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
