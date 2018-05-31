#include "ray_tracer.h"

RayTracer::RayTracer() {
	this->cam = Camera();
}

#include <stdio.h>
Pixel RayTracer::render(int width, int height, int col, int row) {
	double span = 2.0 * tan(PI * cam.fov / 360.0);
	double ratio = span / MAX(width, height);
	double x = ratio * ((col + 0.5) - width/2.0);
	double y = ratio * (-(row + 0.5) + height/2.0);

	Vect rayDir = cam.vx*x + cam.vy*y + cam.dir;
	rayDir.normalize();

	Ray ray = Ray(cam.pos, rayDir);
	return trace(ray);
}

Pixel RayTracer::trace(Ray ray) {
	return (Pixel) { 1.0, 1.0, 0.0 };
}
