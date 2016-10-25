//
// Created by Rob Hendriks on 14/10/2016.
//

#ifndef CITY_DEFENCE_ENGINE_H
#define CITY_DEFENCE_ENGINE_H

#include <memory>
#include <SDL.h>
#include "graphics/display.h"
#include "../config/ini_config.h"
#include "../gui/base_gui.h"

namespace game {

    class engine {
    public:
        void init();
        void setActiveGUI(gui::base_gui* gui);
        void destroy();

    private:
        void load_config();
        void init_display();
        void loop();
        void update(SDL_Event *event);
        void render();

        static const int DISPLAY_WIDTH;
        static const int DISPLAY_HEIGHT;
        static const char *DISPLAY_TITLE;
        static const char *CONFIG_PATH;

        bool m_running;
        gui::base_gui* m_gui = nullptr;
        std::shared_ptr<config::ini_config> m_config;
        std::shared_ptr<graphics::display> m_display;
    };

}

#endif //CITY_DEFENCE_ENGINE_H
