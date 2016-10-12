#include <stdio.h>
#include <iostream>
#include "SDL.h"
#include "config/ini_config.h"

#include "math/box2.hpp"
#include "math/vec2.hpp"

long window_w = 800;
long window_h = 600;

SDL_Window *window;
SDL_Renderer *renderer;

int main(int argc, char *argv[]) {
    math::box2_t a(
        math::vec2_t(0, 0),
        math::vec2_t(12, 12));

    std::cout << a.to_string() << std::endl;
    std::cout << a.center().to_string() << std::endl;


    /*config::ini_config cfg("config.ini");

    if (!cfg.load()) {
        fprintf(stderr, "Failed to load configuration\n");
        return -1;
    }

    window_w = cfg.get("window", "width", window_w);
    window_h = cfg.get("window", "height", window_h);

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Failed to initialize SDL: %s\n", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow("City Defence", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_w, window_h, SDL_WINDOW_SHOWN);
    if (!window) {
        fprintf(stderr, "Failed to create window: %s\n", SDL_GetError());
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        fprintf(stderr, "Failed to create renderer: %s\n", SDL_GetError());
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
    SDL_Quit();*/

    return 0;
}
