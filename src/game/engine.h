//
// Created by Rob Hendriks on 19/10/2016.
//

#ifndef CITY_DEFENCE_ENGINE_H
#define CITY_DEFENCE_ENGINE_H

#include <string>
#include <exception>
#include "window.h"

namespace game {
    class engine {
    public:
        static engine &get();

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

    private:
        window *mWindow;

        bool m_running;
    };
}

#endif //CITY_DEFENCE_ENGINE_H
