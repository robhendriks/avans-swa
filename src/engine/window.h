//
// Created by Rob Hendriks on 19/10/2016.
//

#ifndef CITY_DEFENCE_WINDOW_H
#define CITY_DEFENCE_WINDOW_H

#include <string>
#include <exception>
#include <SDL.h>
#include "window_config.h"
#include "graphics/color4.hpp"
#include "math/box2.hpp"
#include <stdio.h>

namespace engine {
    class window {
    public:
        window(window_config &config);

        void create();

        void clear();

        void present();

        void destroy();

        SDL_Window *get_window() const;

        SDL_Renderer *get_renderer() const;

        static math::box2_t get_screen_box();

        math::box2_t get_display_box();

    private:
        void init_window();

        void init_renderer();

        window_config &mConfig;
        SDL_Window *mWindow;
        SDL_Renderer *mRenderer;
    };
}

#endif //CITY_DEFENCE_WINDOW_H
