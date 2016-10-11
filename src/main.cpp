#include <stdio.h>
#include "SDL2/SDL.h"

const int WIDTH = 800;
const int HEIGHT = 600;

SDL_Window *window;
SDL_Renderer *renderer;

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Failed to initialize SDL: \n", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow("City Defence", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT,
                              SDL_WINDOW_SHOWN);
    if (!window) {
        fprintf(stderr, "Failed to create window: \n", SDL_GetError());
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        fprintf(stderr, "Failed to create renderer: \n", SDL_GetError());
        return 1;
    }

    SDL_SetRenderDrawColor(renderer, 0.0f, 0.0f, 0.0f, 1.0f);

    bool running = true;

    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
