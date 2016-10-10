#include <iostream>
#include "SDL.h"

const int WIDTH = 640;
const int HEIGHT = 480;

SDL_Window *window;

int main(int argc, const char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Failed to initialize SDL: %s\n", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow("City Defence", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        fprintf(stderr, "Failed to create SDL window: %s\n", SDL_GetError());
        return 1;
    }

    bool running = true;

    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
