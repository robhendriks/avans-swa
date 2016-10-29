//
// Created by Rob Hendriks on 19/10/2016.
//

#ifndef CITY_DEFENCE_ENGINE_H
#define CITY_DEFENCE_ENGINE_H

#include <string>
#include <exception>
#include "window.h"
#include "texture/texture_manager.h"

namespace engine {
    class engine {
    public:
        void warmup();

        void run();

        void stop();

        texture::texture_manager& get_texture_manager();
    protected:
        void loop();

        void quit();

        void update();

        void init_sdl();

        void create_window();

    private:
        window* m_window;
        bool m_running;
    };
}

#endif //CITY_DEFENCE_ENGINE_H
