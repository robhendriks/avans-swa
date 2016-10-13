#include <iostream>

#include "SDL.h"
#include "config/ini_config.h"
#include "game/graphics/texture.h"

using namespace game::graphics;

long window_w = 800;
long window_h = 600;

SDL_Window *window;
SDL_Renderer *renderer;

int main(int argc, char *argv[]) {
    config::ini_config cfg("config.ini");

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

    window = SDL_CreateWindow("City Defence", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_w, window_h,
                              SDL_WINDOW_SHOWN);
    if (!window) {
        fprintf(stderr, "Failed to create window: %s\n", SDL_GetError());
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        fprintf(stderr, "Failed to create renderer: %s\n", SDL_GetError());
        return 1;
    }

    int img_flags = IMG_INIT_PNG;
    if (!(IMG_Init(img_flags) & img_flags)) {
        fprintf(stderr, "Failed to initialize SDL_image: %s\n", SDL_GetError());
        return 1;
    }

    /* ---------- TEXTURES ---------- */
    texture tex_a("assets/images/city-defence-logo.png");
    if (!tex_a.load(renderer)) {
        fprintf(stderr, "Failed to load texture: %s\n", SDL_GetError());
        return -1;
    }

    texture tex_b("assets/images/aesthetic-logo.png");
    if (!tex_b.load(renderer)) {
        fprintf(stderr, "Failed to load texture: %s\n", SDL_GetError());
        return -1;
    }
    /* ---------- TEXTURES ---------- */

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    bool running = true;

    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        SDL_RenderClear(renderer);

        SDL_Rect src = {0, 0, tex_a.get_width(), tex_a.get_height()};
        SDL_Rect dst = {(int)((window_w / 2) - 320), (int)((window_h / 2) - 40), 640, 80};

        SDL_RenderCopy(renderer, tex_a.get_texture(), &src, &dst);

        src = {0, 0, tex_b.get_width(), tex_b.get_height()};
        dst = {0, 0, 209, 224};

        SDL_RenderCopy(renderer, tex_b.get_texture(), &src, &dst);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
