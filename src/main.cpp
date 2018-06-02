#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "window.h"
#include "ray_tracer.h"

#define WIDTH 480
#define HEIGHT 480
#define FOV 60
#define SAMPLES 1

int main(int argc, char **argv) {
	// Materials
	Material white = Material(1.0, 1.0, 1.0, 0.6, 0.0);
	Material red = Material(1.0, 0.0, 0.0, 0.2, 0.0);
	Material blue = Material(0.0, 0.0, 1.0, 0.2, 0.0);
	Material green = Material(0.0, 1.0, 0.0, 0.2, 0.0);
	Material blank = Material(0.9, 0.9, 0.9, 0.0, 0.0);
	Material transparent = Material(1.0, 1.0, 1.0, 0.8, 0.8, 1.3);

	// Objects
	std::vector<Object*> objs;
	objs.push_back(new Sphere(white, 0.0, -1.0, 20.0, 4.0));
	objs.push_back(new Sphere(red, -2.0, 3, 17.0, 1.0));
	objs.push_back(new Ellipsoid(blue, 4.0, -2.0, 15.0, 2, 1.2, 1.2));
	objs.push_back(new Sphere(green, -5.0, -5.0, 17.0, 2));
	objs.push_back(new Plane(blank, 0.0, -6.0, 0.0));
	objs.push_back(new Torus(red, 0.0, -2.0, 18.0, 8.0, 1.0));
	objs.push_back(new Sphere(transparent, -3.0, -3.0, 15.0, 2));

	// Lights
	std::vector<Light*> lights;
	lights.push_back(new Light(0.0, 15.0, -15.0, 0.4));
	lights.push_back(new Light(-4.0, 10.0, 5.0, 1.0));
	lights.push_back(new Light(6.0, 2.0, 5.0, 1.0));

	RayTracer *rt = new RayTracer(WIDTH, HEIGHT, FOV, SAMPLES, objs, lights);
	Window *window = new Window("Ray tracer", WIDTH, HEIGHT, rt);

	if (window->init()) {
		while (window->isRunning()) {
			window->handleEvents();
			window->render();
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
