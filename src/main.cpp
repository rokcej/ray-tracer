#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "window.h"
#include "ray_tracer.h"
#include "bitmap.h"

#define WIDTH 1440
#define HEIGHT 1080
#define FOV 60
#define SAMPLES 4

int main(int argc, char **argv) {
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

	Material black = Material(0.05, 0.05, 0.05, 0.2, 0.0);
	Material white2 = Material(255, 255, 255, 0.3, 0.0);

	Material yellow = Material(255, 234, 0, 0.2, 0.0);
	Material orange = Material(255, 179, 0, 0.2, 0.0);
	Material orange2 = Material(245, 124, 0, 0.2, 0.0);

	Material blank = Material(255, 255, 255, 0.0, 0.0);

	// Objects
	std::vector<Object*> objs;
	// Scene 1
	/*objs.push_back(new Sphere(gold, -2.0, 3, 18.0, 1.0));
	objs.push_back(new Ellipsoid(purple, 4.0, -2.0, 16.0, 2, 1.2, 1.2));
	objs.push_back(new Sphere(green, -5.0, -5.0, 18.0, 2));
	objs.push_back(new Sphere(magenta, -4.0, 2.0, 23.0, 2.0));
	objs.push_back(new Plane(lightGrey, 0.0, -6.0, 0.0));
	objs.push_back(new Plane(darkGrey, 0.0, 0.0, 31.0, 0.0, 0.0, -1.0));
	objs.push_back(new Torus(red, 0.0, -2.0, 19.0, 8.0, 1.0));
	objs.push_back(new Sphere(transparent, -3.0, -3.0, 16.0, 2));
	objs.push_back(new Sphere(mirror, 6.0, 3.0, 22.0, 2.0));
	objs.push_back(new TorusY(turquoise, 0.0, -5.0, 22.0, 4.0, 0.6));*/

	// Scene 2
	/*objs.push_back(new Sphere(mirror, 0.0, 0.0, 3.0, 10.0));
	objs.push_back(new Sphere(magenta, 0.0, 0.0, 9.0, 1.5));
	objs.push_back(new Sphere(black, 2.2, 0.0, 7.0, 0.8));
	objs.push_back(new Sphere(white, -2.2, 0.0, 7.0, 0.8));
	objs.push_back(new Torus(darkGrey, 0.0, 0.0, -5.5, 6.8, 1.0));*/

	// Scene 3
	/*objs.push_back(new Plane(white2, 0.0, -4.0, 0.0));
	objs.push_back(new Plane(white, 0.0, 4.0, 0.0));
	objs.push_back(new Plane(white, 0.0, 0.0, 25, 0.0, 0.0, -1.0));
	objs.push_back(new Plane(white, 7.0, 0.0, 0.0, 1.0, 0.0, 0.0));
	objs.push_back(new Plane(white, -7.0, 0.0, 0.0, -1.0, 0.0, 0.0));
	objs.push_back(new Torus(orange2, -1.8, 0.0, 16.0, 3.2, 0.8));
	objs.push_back(new TorusY(orange, 1.8, 0.0, 16.0, 3.2, 0.8));
	objs.push_back(new Sphere(mirror, 0.0, 0.0, -6.0, 6.0));*/

	// Scene 4
	//objs.push_back(new Plane(darkGrey, 0.0, -5.0, 0.0));
	//objs.push_back(new Plane(darkGrey, 0.0, 5.0, 0.0));
	//objs.push_back(new Plane(darkGrey, 0.0, 0.0, 15, 0.0, 0.0, -1.0));
	//objs.push_back(new Plane(darkGrey, 7.0, 0.0, 0.0, 1.0, 0.0, 0.0));
	//objs.push_back(new Plane(darkGrey, -7.0, 0.0, 0.0, -1.0, 0.0, 0.0));
	objs.push_back(new Sphere(blank, 0.0, 0.01, 6.0, 1.0));
	objs.push_back(new Plane(blank, 0.0, -1.0, 0.0));

	// Lights
	std::vector<Light*> lights;
	// Scene 1
	/*lights.push_back(new Light(0.0, 15.0, -15.0, 0.5));
	lights.push_back(new Light(-4.0, 10.0, 5.0, 0.9));
	lights.push_back(new Light(6.0, 2.0, 5.0, 0.9));*/

	// Scene 2
	/*lights.push_back(new Light(0.0, 5.0, -2.0, 0.9));
	lights.push_back(new Light(-5.0, 4.0, 3.0, 0.05, 0.355, 0.61));
	lights.push_back(new Light(5.0, -4.0, 4.0, 0.5, 0.2, 0.0));*/

	// Scene 3
	/*lights.push_back(new Light(4.0, 2.9, 2.0, 0.98));
	lights.push_back(new Light(-4.0, -2.9, -2.0, 0.27, 0.0, 0.05));*/

	// Scene 4
	lights.push_back(new Light(4.0, 4.0, -4.0, 1.0));

	// Renderer
	RayTracer *rt = new RayTracer(WIDTH, HEIGHT, FOV, SAMPLES, objs, lights);

	// If the argument `bmp` is passed, save image into a .bmp file,
	// otherwise render it directly to the screen
	if (argc > 1 && strcmp(argv[1], "bmp") == 0) {
		// Save image to a file
		Vect **image = rt->render();
		bmpSaveImage(image, WIDTH, HEIGHT, "render.bmp");
	} else { 
		// Render image to the screen
		Window *window = new Window("Ray tracer", WIDTH, HEIGHT, rt);

		if (window->init()) {
			while (window->isRunning()) {
				window->handleEvents();
				window->render();
			}
			window->close();
		}
		
		delete window;
	}
	
	// Free memory
	for (int i = 0; i < objs.size(); ++i)
		delete objs.at(i);
	for (int i = 0; i < lights.size(); ++i)
		delete lights.at(i);
	delete rt;
	return 0;
}
