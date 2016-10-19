//
// Created by Rob Hendriks on 19/10/2016.
//

#include "window.h"

namespace game {
    window::window(window_config config) : mConfig(config), mWindow(NULL), mRenderer(NULL) {}

    window::~window() {}

    void window::create() {
        printf("[DEBUG] Creating window...\n");

        init_window();
        init_renderer();
    }

    void window::init_window() {
        if (mWindow) {
            return;
        }

        mWindow = SDL_CreateWindow(mConfig.title, mConfig.x, mConfig.y, mConfig.w, mConfig.h, mConfig.flags);

        if (!mWindow) {
            std::string error = SDL_GetError();
            throw std::runtime_error("Failed to create window: " + error);
        }
    }

    void window::init_renderer() {
        if (mRenderer) {
            return;
        }

        mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);

        if (!mRenderer) {
            std::string error = SDL_GetError();
            throw std::runtime_error("Failed to create renderer: " + error);
        }
    }

    void window::clear() {
        SDL_SetRenderDrawColor(mRenderer, BACKGROUND_COLOR.r, BACKGROUND_COLOR.g, BACKGROUND_COLOR.b, BACKGROUND_COLOR.a);
        SDL_RenderClear(mRenderer);
    }

    void window::present() {
        SDL_RenderPresent(mRenderer);
    }

    void window::destroy() {
        printf("[DEBUG] Destroying window...\n");

        if (mRenderer) {
            SDL_DestroyRenderer(mRenderer);
        }
        if (mWindow) {
            SDL_DestroyWindow(mWindow);
        }
    }

    SDL_Window *window::get_window() const {
        return mWindow;
    }

    SDL_Renderer *window::get_renderer() const {
        return mRenderer;
    }

    const graphics::color4_t window::BACKGROUND_COLOR = graphics::color4_t(0xFF6495ED);
}