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
// Macros
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define ABS(x) ((x) < 0 ? -(x) : (x))

class RayTracer {
private:
	int samples;
	double rayStepSize;
	int maxRaySteps;
	int maxRayDepth;
	double rayTol;
	int maxIter;

	Camera cam;
	std::vector<Object*> objs;
	std::vector<Light*> lights;
	Vect **pixels;

	static void renderRow(RayTracer *rt, int row, double ratio, double sampleSize);
	Vect trace(Ray& ray, int depth, int currentSteps, int *signsPrev);
	Vect traceShadow(Vect& origin, Vect& normal, int *signsPrev, int signPrev);
	double newton(Object* obj, Ray& ray, double t, double tol, int max_iter);
public:
	RayTracer(int width, int height, int fov, int samples, double rayStepSize, int maxRaySteps, int maxRayDepth, double rayTol, int maxIter);
	~RayTracer();
	Vect **render();
	void setCamPos(double x, double y, double z);
	void setCamDir(double x, double y, double z);
	void addObject(Object* obj);
	void addLight(Light* light);
};

#endif
