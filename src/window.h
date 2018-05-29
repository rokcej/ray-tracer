#ifndef _window_h
#define _window_h

#include <SDL2/SDL.h>
#include "ray_tracer.h"

class Window {
private:
	const char *title;
	int width;
	int height;
	int running;
	RayTracer *rt;
	SDL_Window *window;
	SDL_Renderer *renderer;
public:
	Window(const char *title, int width, int height, RayTracer *rt);

	int init();
	int isRunning();
	void render();
	void handleEvents();
	void close();
};

#endif
