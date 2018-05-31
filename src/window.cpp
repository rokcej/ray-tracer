#include "window.h"

Window::Window(const char *title, int width, int height, RayTracer *rt) {
	this->title = title;
	this->width = width;
	this->height = height;
	this->rt = rt;
	this->running = 1;
	rendering = 1; // REMOVE
}

int Window::init() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "Failed to initialize SDL: %s\n", SDL_GetError());
		return 0;
	}
	this->window = SDL_CreateWindow(
		this->title,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		this->width,
		this->height,
		SDL_WINDOW_SHOWN //| SDL_WINDOW_RESIZABLE
	);
	if (this->window == NULL) {
		fprintf(stderr, "Failed to create SDL Window: %s\n", SDL_GetError());
		SDL_Quit();
		return 0;
	}
	this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (this->renderer == NULL) {
		fprintf(stderr, "Failed to create SDL Renderer: %s\n", SDL_GetError());
		SDL_DestroyWindow(this->window);
		SDL_Quit();
		return 0;
	}
	return 1;
}

int Window::isRunning() {
	return running;
}

void Window::render() {
	if (rendering) { // REMOVE
		rendering = 0;
		SDL_RenderClear(renderer);

		for (int y = 0; y < this->height; y++) {
			for (int x = 0; x < this->width; x++) {
				Pixel p = rt->render(width, height, x, y);
				SDL_SetRenderDrawColor(renderer, round(p.r*255.0), round(p.g*255.0), round(p.b*255.0), 255);
				SDL_RenderDrawPoint(renderer, x, y);
			}
		}

		SDL_RenderPresent(renderer);
	}
}

void Window::handleEvents() {
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		switch (e.type) {
		case SDL_QUIT:
			this->running = 0;
			break;
		/*case SDL_WINDOWEVENT:
			if (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
				SDL_GetWindowSize(window, &(this->width), &(this->height));
			break;*/
		default:
			break;
		}
	}
}

void Window::close() {
	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);
	SDL_Quit();
}
