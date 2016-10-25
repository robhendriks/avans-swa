//
// Created by Rob Hendriks on 19/10/2016.
//

#ifndef CITY_DEFENCE_WINDOW_H
#define CITY_DEFENCE_WINDOW_H

#include <string>
#include <exception>
#include <SDL.h>
#include "window_config.h"
#include <stdio.h>
#include "../graphics/color4.hpp"

namespace game {
    class window {
    public:
        window(window_config config);

        ~window();

        void create();

        void clear();

        void present();

        void destroy();

        SDL_Window *get_window() const;

        SDL_Renderer *get_renderer() const;

    private:
        void init_window();

        void init_renderer();

        window_config mConfig;
        SDL_Window *mWindow;
        SDL_Renderer *mRenderer;

        static const graphics::color4_t BACKGROUND_COLOR;
    };
}

#endif //CITY_DEFENCE_WINDOW_H
