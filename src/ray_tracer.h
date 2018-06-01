#ifndef _ray_tracer_h
#define _ray_tracer_h

#include "vect.h"
#include "entity.h"
#include "camera.h"
#include "ray.h"
#include <math.h>
#include <vector>
#include <stdio.h>

// Constants
#define PI 3.14159265358979323846
// Parameters
#define STEP_SIZE 0.2
#define MAX_STEPS 100
#define MAX_DEPTH 10
#define TOL 1e-8
#define MAX_ITER 10
// Macros
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
	void *getSigns(Vect& point, int *signs);
	Vect render(int width, int height, int col, int row);
	Vect trace(Ray& ray, int depth);
	Vect traceShadow(Vect origin, int *signs);
	double newton(Object* obj, Ray& ray, double t, double tol, int max_iter);
};

#endif
