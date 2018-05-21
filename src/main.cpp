#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "window.h"
#include "ray_tracer.h"

int main(int argc, char **argv) {
    Window *window = new Window("Ray tracer", 640, 480);
    if (!window->init())
        return 1;

    while (window->isRunning()) {
        window->handleEvents();
        window->render();
    }

    window->close();
    delete window;
    return 0;
}
