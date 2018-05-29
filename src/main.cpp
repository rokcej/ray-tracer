#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "window.h"
#include "ray_tracer.h"

int main(int argc, char **argv) {
	RayTracer *rt = new RayTracer();
	Window *window = new Window("Ray tracer", 640, 480, rt);

	if (window->init()) {
		while (window->isRunning()) {
			window->handleEvents();
			window->render();
		}
		
		window->close();
	}
	
	delete window;
	delete rt;
	return 0;
}
