#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "window.h"
#include "ray_tracer.h"

int main(int argc, char **argv) {
	std::vector<Object*> objs;
	objs.push_back(new Sphere(0.0, -1.0, 11.0, 4.0));
	objs.push_back(new Sphere(-2.0, 3, 8.0, 1.0));

	std::vector<Light*> lights;
	lights.push_back(new Light(-4.0, 10.0, 5.0, 0.2));
	lights.push_back(new Light(6.0, 2.0, 5.0, 0.2));

	RayTracer *rt = new RayTracer(objs, lights);
	Window *window = new Window("Ray tracer", 360, 360, rt);

	if (window->init()) {
		int rendered = 0; // Render only 1 frame, remove
		while (window->isRunning()) {
			window->handleEvents();
			if (!rendered) {
				rendered = 1;
				window->render();
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
