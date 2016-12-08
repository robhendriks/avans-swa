//
// Created by Rob Hendriks on 19/10/2016.
//

#include "window.h"
#include "events/display_changed.h"
#include "eventbus/eventbus.h"

namespace engine {
    window::window(window_config &config) : mConfig(config), mWindow(NULL), mRenderer(NULL) {}

    void window::create() {
        printf("[DEBUG] Creating window...\n");

        init_window();
        init_renderer();
    }

    void window::init_window() {
        if (mWindow) {
            return;
        }

        // When the width or height is smaller than 0, use the full width/height
        bool set_fullscreen = false;
        if (mConfig.w < 0 || mConfig.h < 0) {
            if (mConfig.w < 0 && mConfig.h < 0) {
                set_fullscreen = true;
            }
            auto box = get_screen_box();
            if (mConfig.w < 0) {
                mConfig.w = (int)box.width();
            }
            if (mConfig.h < 0) {
                mConfig.h = (int)box.height();
            }
        }

        mWindow = SDL_CreateWindow(mConfig.title.c_str(), mConfig.x, mConfig.y, mConfig.w, mConfig.h, mConfig.flags);

        if (set_fullscreen && !mConfig.debug) {
            // Set fullscreen mode
            SDL_SetWindowFullscreen(mWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
        }

        if (!mWindow) {
            std::string error = SDL_GetError();
            throw std::runtime_error("Failed to create window: " + error);
        }
    }

    void window::init_renderer() {
        if (mRenderer) {
            return;
        }

        mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (!mRenderer) {
            std::string error = SDL_GetError();
            throw std::runtime_error("Failed to create renderer: " + error);
        }
    }

    void window::clear() {
        SDL_SetRenderDrawColor(mRenderer, mConfig.background_color.r, mConfig.background_color.g, mConfig.background_color.b, mConfig.background_color.a);
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

    math::box2_t window::get_screen_box() {
        SDL_DisplayMode dm;
        if (SDL_GetDesktopDisplayMode(0, &dm) != 0) {
            SDL_Log("SDL_GetDesktopDisplayMode failed: %s", SDL_GetError());
        }

        return math::box2_t({{0, 0}, {(float)dm.w, (float)dm.h}});
    }

    math::box2_t window::get_display_box() const {
#ifdef __APPLE__
        int w, h;
        SDL_GetWindowSize(mWindow, &w, &h);
        return {0, 0, static_cast<float>(w), static_cast<float>(h)};
#else
        auto surface = *get_surface();
        return math::box2_t({{0, 0}, {(float)surface.w, (float)surface.h}});
#endif
    }

    SDL_Surface *window::get_surface() const {
        return SDL_GetWindowSurface(mWindow);
    }

    void window::trigger_display_change() const {
        auto *display_event = new events::display_changed(get_display_box());
        eventbus::eventbus::get_instance().fire(display_event);
        delete display_event;
    }
}
