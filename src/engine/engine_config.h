//
// Created by robbie on 1-11-2016.
//

#ifndef CITY_DEFENCE_ENGINE_CONFIG_H
#define CITY_DEFENCE_ENGINE_CONFIG_H

#include "window_config.h"

namespace engine {
    struct engine_config {
        engine_config(window_config &win_config) : win_config(win_config) {}
        window_config &win_config;
        int ticks_per_second = 50;
        int skip_ticks = 1000;
        int max_frameskip = 5;

        int get_skip_ticks() {
            return skip_ticks / ticks_per_second;
        }
    };
}

#endif //CITY_DEFENCE_ENGINE_CONFIG_H
