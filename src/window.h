#ifndef _window_h
#define _window_h

#include <SDL2/SDL.h>
#include "ray_tracer.h"
#include <stdio.h>
#include <math.h>

class Window {
private:
	const char *title;
	int width;
	int height;
	int running;
	RayTracer *rt;
	SDL_Window *window;
	SDL_Renderer *renderer;

	Vect **pixels = NULL; // For debugging, only render one frame, remove this
public:
	Window(const char *title, int width, int height, RayTracer *rt);

	int init();
	int isRunning();
	void render();
	void handleEvents();
	void close();
};

#endif
