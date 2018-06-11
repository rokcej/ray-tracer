#include "ray_tracer.h"
#include "bitmap.h"

// Parameters
// Basic
#define FILE_NAME "render.bmp" // Name of the file to save the image in
#define WIDTH 640 // Image x resolution
#define HEIGHT 480 // Image y resolution
#define FOV 60 // Camera field of view
#define NUM_SAMPLES 1 // Number of samples per row and column of each pixel
#define NUM_THREADS 8 // Number of threads to run the program on
// Advanced
#define RAY_STEP_SIZE 0.1 // Size of a step when tracing a ray
#define MAX_RAY_STEPS 300 // Number of steps a ray travels
#define MAX_RAY_DEPTH 40 // Maximum recursion depth when tracing reflections/refractions
#define RAY_TOL 1e-14 // Maximum accuracy when calculating collision point
#define MAX_ITER 20 // Maximum number of newton's iterations when calculating collision point

int main(int argc, char **argv) {
	// Renderer
	RayTracer *rt = new RayTracer(WIDTH, HEIGHT, FOV, NUM_SAMPLES, NUM_THREADS, RAY_STEP_SIZE, MAX_RAY_STEPS, MAX_RAY_DEPTH, RAY_TOL, MAX_ITER);

	// Materials
	Material mirror = Material(255, 255, 255, 0.9, 0.0);
	Material blank = Material(255, 255, 255, 0.0, 0.0);

	// Objects and lights
	rt->addObject(new Sphere(mirror, 0.0, 0.2, 8.0, 1.5));
	rt->addObject(new Sphere(blank, -1.8, -0.3, 6.0, 0.8));
	rt->addObject(new Sphere(blank, 1.8, -0.3, 6.0, 0.8));
	rt->addObject(new Plane(blank, 0.0, -1.31, 0.0));

	rt->addLight(new Light(2.0, 2.0, 0.0, 1.0));
	rt->addLight(new Light(0.0, 0.0, 0.0, 0.2));

	// Render image to a .bmp file
	Vect **image = rt->render();
	bmpSaveImage(image, WIDTH, HEIGHT, FILE_NAME);

	// Free memory
	delete rt;
	return 0;
}
