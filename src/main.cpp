#include "ray_tracer.h"
#include "bitmap.h"

// Parameters
// Basic
#define FILE_NAME "render.bmp" // Name of the file to save the image in
#define WIDTH 640 // Image x resolution
#define HEIGHT 480 // Image y resolution
#define FOV 60 // Camera field of view
#define SAMPLES 3 // Number of samples per row and column of each pixel
// Advanced
#define RAY_STEP_SIZE 0.1 // Size of a step when tracing a ray
#define MAX_RAY_STEPS 600 // Number of steps a ray travels
#define MAX_RAY_DEPTH 40 // Maximum recursion depth when tracing reflections/refractions
#define RAY_TOL 1e-12 // Maximum accuracy when calculating collision point
#define MAX_ITER 20 // Maximum number of newton's iterations when calculating collision point

int main(int argc, char **argv) {
	// Renderer
	RayTracer *rt = new RayTracer(WIDTH, HEIGHT, FOV, SAMPLES, RAY_STEP_SIZE, MAX_RAY_STEPS, MAX_RAY_DEPTH, RAY_TOL, MAX_ITER);

	// Materials
	Material mirror = Material(255, 255, 255, 0.9, 0.0);
	Material white = Material(255, 255, 255, 0.05, 0.0);
	Material cyan = Material(26, 235, 242, 0.2, 0.0);
	Material red = Material(237, 50, 46, 0.2, 0.0);
	Material gold = Material(243, 156, 18, 0.2, 0.0);
	Material purple = Material(107, 11, 122, 0.2, 0.0);
	Material green = Material(21, 230, 33, 0.3, 0.0);
	Material lightGrey = Material(0.8, 0.8, 0.8, 0.0, 0.0);
	Material darkGrey = Material(0.2, 0.2, 0.2, 0.0, 0.0);
	Material transparent = Material(255, 255, 255, 0.9, 0.9, 1.4);
	Material magenta = Material(242, 12, 173, 0.2, 0.0);
	Material turquoise = Material(46, 221, 140, 0.6, 0.0);

	Material black = Material(0.05, 0.05, 0.05, 0.05, 0.0);
	Material white2 = Material(255, 255, 255, 0.3, 0.0);

	Material yellow = Material(255, 234, 0, 0.2, 0.0);
	Material orange = Material(255, 179, 0, 0.2, 0.0);
	Material orange2 = Material(245, 124, 0, 0.2, 0.0);

	Material blank = Material(255, 255, 255, 0.0, 0.0);

	Material green2 = Material(79, 242, 101, 0.2, 0.0);
	Material green3 = Material(20, 186, 61, 0.2, 0.0);
	Material darkerGrey = Material(0.15, 0.15, 0.15, 0.15, 0.0);
	Material magenta2 = Material(242, 19, 234, 0.3, 0.0);
	Material transparent2 = Material(255, 255, 255, 0.9, 0.9, 1.1);

	// Objects and lights
	// Scene 1
	/*rt->addObject(new Sphere(gold, -2.0, 3, 18.0, 1.0));
	rt->addObject(new Ellipsoid(purple, 4.0, -2.0, 16.0, 2, 1.2, 1.2));
	rt->addObject(new Sphere(green, -5.0, -5.0, 18.0, 2));
	rt->addObject(new Sphere(magenta, -4.0, 2.0, 23.0, 2.0));
	rt->addObject(new Plane(lightGrey, 0.0, -6.0, 0.0));
	rt->addObject(new Plane(darkGrey, 0.0, 0.0, 31.0, 0.0, 0.0, -1.0));
	rt->addObject(new Torus(red, 0.0, -2.0, 19.0, 8.0, 1.0));
	rt->addObject(new Sphere(transparent, -3.0, -3.0, 16.0, 2));
	rt->addObject(new Sphere(mirror, 6.0, 3.0, 22.0, 2.0));
	rt->addObject(new TorusY(turquoise, 0.0, -5.0, 22.0, 4.0, 0.6));

	rt->addLight(new Light(0.0, 15.0, -15.0, 0.5));
	rt->addLight(new Light(-4.0, 10.0, 5.0, 0.9));
	rt->addLight(new Light(6.0, 2.0, 5.0, 0.9));*/

	// Scene 2
	/*rt->addObject(new Sphere(mirror, 0.0, 0.0, 3.0, 10.0));
	rt->addObject(new Sphere(magenta, 0.0, 0.0, 9.0, 1.5));
	rt->addObject(new Sphere(black, 2.2, 0.0, 7.0, 0.8));
	rt->addObject(new Sphere(white, -2.2, 0.0, 7.0, 0.8));
	rt->addObject(new Torus(darkGrey, 0.0, 0.0, -5.5, 6.8, 1.0));
	
	rt->addLight(new Light(0.0, 5.0, -2.0, 0.9));
	rt->addLight(new Light(-5.0, 4.0, 3.0, 0.05, 0.355, 0.61));
	rt->addLight(new Light(5.0, -4.0, 4.0, 0.5, 0.2, 0.0));*/

	// Scene 3
	/*rt->addObject(new Plane(white2, 0.0, -4.0, 0.0));
	rt->addObject(new Plane(white, 0.0, 4.0, 0.0));
	rt->addObject(new Plane(white, 0.0, 0.0, 25, 0.0, 0.0, -1.0));
	rt->addObject(new Plane(white, 7.0, 0.0, 0.0, 1.0, 0.0, 0.0));
	rt->addObject(new Plane(white, -7.0, 0.0, 0.0, -1.0, 0.0, 0.0));
	rt->addObject(new Torus(orange2, -1.8, 0.0, 16.0, 3.2, 0.8));
	rt->addObject(new TorusY(orange, 1.8, 0.0, 16.0, 3.2, 0.8));
	rt->addObject(new Sphere(mirror, 0.0, 0.0, -6.0, 6.0));

	rt->addLight(new Light(4.0, 2.9, 2.0, 0.98));
	rt->addLight(new Light(-4.0, -2.9, -2.0, 0.27, 0.0, 0.05));*/

	// Scene 4
	//rt->addObject(new Sphere(blank, 0.0, 0.01, 6.0, 1.0));
	//rt->addObject(new Plane(blank, 0.0, -1.0, 0.0));
	rt->addObject(new Plane(darkerGrey, 0.0, -5.0, 0.0));
	rt->addObject(new Plane(darkerGrey, 0.0, 5.0, 0.0));
	rt->addObject(new Plane(darkerGrey, 0.0, 0.0, 22, 0.0, 0.0, -1.0));
	rt->addObject(new Plane(darkerGrey, 7.0, 0.0, 0.0, 1.0, 0.0, 0.0));
	rt->addObject(new Plane(darkerGrey, -7.0, 0.0, 0.0, -1.0, 0.0, 0.0));
	rt->addObject(new Torus(green2, -1.8, 0.0, 16.0, 3.2, 0.8));
	rt->addObject(new TorusY(green3, 1.8, 0.0, 16.0, 3.2, 0.8));
	rt->addObject(new Sphere(magenta2, 3.5, -2.5, 16.0, 1.8));
	rt->addObject(new Sphere(mirror, 0.0, 0.0, -6.1, 6.0));
	rt->addObject(new Sphere(transparent2, 1.0, -1.0, 10.0, 1.5));
	rt->addObject(new Sphere(white, -1.8, -1.0, 19.0, 2.8));

	rt->addLight(new Light(0.0, 3.0, 0.0, 0.8));
	rt->addLight(new Light(4.0, 3.0, 0.0, 0.9));
	rt->addLight(new Light(-4.0, -3.0, 0.0, 0.4));

	// Remder image to a .bmp file
	Vect **image = rt->render();
	bmpSaveImage(image, WIDTH, HEIGHT, FILE_NAME);

	// Free memory
	delete rt;
	return 0;
}
