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
        void setActiveGUI(gui::base_gui* gui);
        void run();

        void loop();

    protected:
        engine() {}

        ~engine() {}

        engine(const engine &e) = delete;

        engine &operator=(const engine &e) = delete;

        void quit();

        void init_sdl();

        void create_window();

    private:
        gui::base_gui* mActiveGUI;
        window *mWindow;
    };
}

#endif //CITY_DEFENCE_ENGINE_H
