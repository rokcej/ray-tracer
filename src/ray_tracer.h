#ifndef _ray_tracer_h
#define _ray_tracer_h

#include "vect.h"
#include "object.h"
#include "camera.h"
#include "ray.h"
#include <math.h>
#include <vector>

#define PI 3.14159265358979323846
#define STEP_SIZE 0.05
#define MAX_STEPS 1000
#define MAX_DEPTH 10
#define TOL 1e-8
#define MAX_ITER 5
#define MAX(x, y) (((x) > (y)) ? (x) : (y))

typedef struct {
	double r;
	double g;
	double b;
} Pixel;

class RayTracer {
private:
	Camera cam;
	std::vector<Object*> objs;
public:
	RayTracer(std::vector<Object*>& objs);
	Pixel render(int wRaw, int hRaw, int xRaw, int yRaw);
	Pixel trace(Ray& ray, int depth);
	double newton(Object* obj, Ray& ray, double t, double tol, int max_iter);
};

#endif
