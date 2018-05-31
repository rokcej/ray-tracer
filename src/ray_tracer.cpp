#include "ray_tracer.h"
#include <stdio.h>

RayTracer::RayTracer(std::vector<Object*>& objs) {
	this->cam = Camera();
	this->objs = objs;
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
	int n = objs.size();
	int signs[n];
	for (int i = 0; i < n; ++i)
		signs[i] = objs.at(i)->f(ray.origin) >= 0; // TODO: If == 0

	for (int step = 1; step < MAX_STEPS; ++step) {
		for (int i = 0; i < n; ++i) {
			int sign = objs.at(i)->f(ray.origin + ray.dir * (step * STEP_SIZE)) >= 0; // TODO: Change to addition if slow
			if (sign != signs[i]) {
				// Calculate collision
				double t = newton(objs.at(i), ray, (step -0.5 ) * STEP_SIZE, TOL, MAX_ITER);
				double a = 1 - t / 10;
				printf("a: %lf, t: %lf, step: %d\n", a, t, step);
				return (Pixel) { a, a, a };
			}
		}
	}
	return (Pixel) { 0.0, 0.0, 0.0 };
}


double RayTracer::newton(Object* obj, Ray& ray, double t, double tol, int max_iter) {
	double t0 = t;
	for (int i = 0; i < max_iter; ++i) {
		Vect v = ray.origin + ray.dir * t0;
		t = t0 - obj->f(v) / (ray.dir.x * obj->dfx(v) + ray.dir.y * obj->dfy(v) + ray.dir.z * obj->dfz(v));
		//printf("t: %lf, iter: %d\n", t, i);
		if (t - t0 < tol)
			break;
		t0 = t;
	}
	//printf("t: %lf\n", t);
	return t;
}
