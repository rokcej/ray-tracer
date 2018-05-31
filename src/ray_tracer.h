#ifndef _ray_tracer_h
#define _ray_tracer_h

#include "vect.h"
#include "entity.h"
#include "camera.h"
#include "ray.h"
#include <math.h>
#include <vector>
#include <stdio.h>

#define PI 3.14159265358979323846
#define STEP_SIZE 0.1
#define MAX_STEPS 500
#define MAX_DEPTH 10
#define TOL 1e-8
#define MAX_ITER 5
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define ABS(x) ((x) < 0 ? -(x) : (x))

typedef struct {
	double r;
	double g;
	double b;
} Pixel;

class RayTracer {
private:
	Camera cam;
	std::vector<Object*> objs;
	std::vector<Light*> lights;
public:
	RayTracer(std::vector<Object*>& objs, std::vector<Light*>& lights);
	Pixel render(int wRaw, int hRaw, int xRaw, int yRaw);
	Pixel trace(Ray& ray, int depth);
	double newton(Object* obj, Ray& ray, double t, double tol, int max_iter);
};

#endif
