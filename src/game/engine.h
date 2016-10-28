//
// Created by Rob Hendriks on 19/10/2016.
//

#ifndef CITY_DEFENCE_ENGINE_H
#define CITY_DEFENCE_ENGINE_H

#include <string>
#include <exception>
#include "window.h"
#include "../gui/base_gui.h"

namespace game {
    class engine {
    public:
        static engine &get();
        void set_active_gui(gui::base_gui* gui);
        void run();

        void loop();

        void update();

        void render(float interpolation);

    protected:
        engine() {}

        ~engine() {}

        engine(const engine &e) = delete;

        engine &operator=(const engine &e) = delete;

        void quit();

        void init_sdl();

        void create_window();
        void create_texture_manager(SDL_Renderer *r);

    private:
        gui::base_gui* m_active_gui;
        window* m_window;
        texture::texture_manager * texture_manager;
        bool m_running;
    };
}

#endif //CITY_DEFENCE_ENGINE_H
