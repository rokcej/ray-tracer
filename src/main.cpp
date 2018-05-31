#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "window.h"
#include "ray_tracer.h"

int main(int argc, char **argv) {
	std::vector<Object*> objs;
	objs.push_back(new Sphere(0.0, 0.0, 10.0, 4.0));

	RayTracer *rt = new RayTracer(objs);
	Window *window = new Window("Ray tracer", 360, 360, rt);

	if (window->init()) {
		while (window->isRunning()) {
			window->handleEvents();
			window->render();
		}
		
		window->close();
	}
	
	for (int i = 0; i < objs.size(); ++i)
		delete objs.at(i);
	delete window;
	delete rt;
	return 0;
}
