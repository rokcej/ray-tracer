#ifndef _ray_tracer_h
#define _ray_tracer_h

#include "vect.h"
#include "entity.h"
#include "camera.h"
#include "ray.h"
#include <math.h>
#include <vector>
#include <stdio.h>
#include <time.h>
#include <thread>

// Constants
#define PI 3.14159265358979323846
// Parameters
#define RAY_STEP_SIZE 0.1
#define MAX_RAY_STEPS 1200
#define MAX_RAY_DEPTH 40
#define RAY_TOL 1e-12
#define MAX_ITER 20
// Macros
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define ABS(x) ((x) < 0 ? -(x) : (x))

class RayTracer {
private:
	Camera cam;
	int samples;
	std::vector<Object*> objs;
	std::vector<Light*> lights;
	Vect **pixels;

	static void renderRow(RayTracer *rt, int row, double ratio, double sampleSize);
	Vect trace(Ray& ray, int depth, int currentSteps, int *signsPrev);
	Vect traceShadow(Vect& origin, Vect& normal, int *signsPrev, int signPrev);
	double newton(Object* obj, Ray& ray, double t, double tol, int max_iter);
public:
	RayTracer(int width, int height, int fov, int samples, std::vector<Object*>& objs, std::vector<Light*>& lights);
	~RayTracer();
	Vect **render();
	void setCamPos(double x, double y, double z);
	void setCamDir(double x, double y, double z);
};

#endif
