#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "window.h"
#include "ray_tracer.h"
#include "bitmap.h"

#define WIDTH 640
#define HEIGHT 480
#define FOV 60
#define SAMPLES 1

int main(int argc, char **argv) {
	// Materials
	Material mirror = Material(255, 255, 255, 0.9, 0.0);
	Material white = Material(255, 255, 255, 0.05, 0.0);
	Material cyan = Material(26, 235, 242, 0.2, 0.0);
	Material red = Material(237, 50, 46, 0.2, 0.0);
	Material gold = Material(243, 156, 18, 0.2, 0.0);
	Material blue = Material(41, 98, 217, 0.1, 0.0);
	Material green = Material(21, 230, 33, 0.3, 0.0);
	Material lightGrey = Material(0.8, 0.8, 0.8, 0.0, 0.0);
	Material darkGrey = Material(0.2, 0.2, 0.2, 0.0, 0.0);
	Material transparent = Material(255, 255, 255, 0.9, 0.9, 1.4);
	Material magenta = Material(242, 12, 173, 0.2, 0.0);

	// Objects
	std::vector<Object*> objs;
	objs.push_back(new Sphere(cyan, 0.0, -1.0, 20.0, 4.0));
	objs.push_back(new Sphere(gold, -2.0, 3, 17.0, 1.0));
	objs.push_back(new Ellipsoid(blue, 4.0, -2.0, 15.0, 2, 1.2, 1.2));
	objs.push_back(new Sphere(green, -5.0, -5.0, 17.0, 2));
	objs.push_back(new Sphere(magenta, -4.0, 2.0, 22.0, 2.0));
	objs.push_back(new Plane(lightGrey, 0.0, -6.0, 0.0));
	objs.push_back(new Plane(darkGrey, 0.0, 0.0, 30.0, 0.0, 0.0, -1.0));
	objs.push_back(new Torus(red, 0.0, -2.0, 18.0, 8.0, 1.0));
	objs.push_back(new Sphere(transparent, -3.0, -3.0, 15.0, 2));
	objs.push_back(new Sphere(mirror, 6.0, 3.0, 21.0, 2.0));

	// Lights
	std::vector<Light*> lights;
	lights.push_back(new Light(0.0, 15.0, -15.0, 0.4));
	lights.push_back(new Light(-4.0, 10.0, 5.0, 1.0));
	lights.push_back(new Light(6.0, 2.0, 5.0, 1.0));

	// Renderer
	RayTracer *rt = new RayTracer(WIDTH, HEIGHT, FOV, SAMPLES, objs, lights);

	// Camera
	rt->setCamPos(0.0, 0.0, -1.0);

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
