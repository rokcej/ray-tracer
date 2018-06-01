#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "window.h"
#include "ray_tracer.h"

#define WIDTH 480
#define HEIGHT 480
#define FOV 60
#define SAMPLES 2

int main(int argc, char **argv) {
	// Materials
	Material white = Material(1.0, 1.0, 1.0, 0.6, 0.0);
	Material red = Material(1.0, 0.0, 0.0, 0.2, 0.0);
	Material blue = Material(0.0, 0.0, 1.0, 0.2, 0.0);
	Material green = Material(0.0, 1.0, 0.0, 0.2, 0.0);
	Material blank = Material(0.9, 0.9, 0.9, 0.0, 0.0);

	// Objects
	std::vector<Object*> objs;
	objs.push_back(new Sphere(white, 0.0, -1.0, 18.0, 4.0));
	objs.push_back(new Sphere(red, -2.0, 3, 15.0, 1.0));
	objs.push_back(new Sphere(blue, 3.0, -2.0, 13.0, 1.2));
	objs.push_back(new Sphere(green, -4.0, -5.0, 15.0, 2));
	objs.push_back(new Plane(blank, 0.0, -6.0, 0.0));

	// Lights
	std::vector<Light*> lights;
	lights.push_back(new Light(-4.0, 10.0, 5.0, 1.0));
	lights.push_back(new Light(6.0, 2.0, 5.0, 1.0));

	RayTracer *rt = new RayTracer(WIDTH, HEIGHT, FOV, SAMPLES, objs, lights);
	Window *window = new Window("Ray tracer", WIDTH, HEIGHT, rt);

	if (window->init()) {
		int rendered = 0; // Render only 1 frame, remove
		while (window->isRunning()) {
			window->handleEvents();
			if (!rendered) {
				rendered = 1;
				clock_t start = clock();
				window->render();
				double render_time = (double)(clock() - start) / CLOCKS_PER_SEC;
				printf("Frame render time: %lfs\n", render_time);
			}
		}
		
		window->close();
	}
	
	for (int i = 0; i < objs.size(); ++i)
		delete objs.at(i);
	for (int i = 0; i < lights.size(); ++i)
		delete lights.at(i);
	delete window;
	delete rt;
	return 0;
}
