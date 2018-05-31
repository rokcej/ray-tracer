#ifndef _ray_tracer_h
#define _ray_tracer_h

#include "vect.h"
#include "object.h"
#include "camera.h"
#include "ray.h"
#include <math.h>

#define PI 3.14159265358979323846
#define MAX(x, y) (((x) > (y)) ? (x) : (y))

typedef struct {
	double r;
	double g;
	double b;
} Pixel;

class RayTracer {
private:
	Camera cam;
public:
	RayTracer();
	Pixel render(int wRaw, int hRaw, int xRaw, int yRaw);
	Pixel trace(Ray ray);
};

#endif
