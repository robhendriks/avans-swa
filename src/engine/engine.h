//
// Created by Rob Hendriks on 19/10/2016.
//

#ifndef CITY_DEFENCE_ENGINE_H
#define CITY_DEFENCE_ENGINE_H

#include <string>
#include <exception>
#include "window.h"
#include "graphics/texture_manager.h"
#include "engine_config.h"
#include "graphics/color_manager.h"

namespace engine {
    class engine {
    public:
        engine(engine_config config);

        void warmup();

        void run();

        void stop();

        graphics::texture_manager *get_texture_manager() const;

        graphics::color_manager *get_color_manager() const;

        window *get_window() const;
    protected:
        void loop();

        void quit();

        void update();

        void init_sdl();

        void create_window();

    private:
        window* m_window;
        bool m_running;
        engine_config m_config;
    };
}

#endif //CITY_DEFENCE_ENGINE_H
