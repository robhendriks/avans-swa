//
// Created by Rob Hendriks on 19/10/2016.
//

#ifndef CITY_DEFENCE_CONFIG_H
#define CITY_DEFENCE_CONFIG_H

#include <json.hpp>
#include "../config/json_config.h"

namespace engine {
    class settings {
    public:
        static settings &get();

        unsigned int get_window_width() const;

        unsigned int get_window_height() const;

    private:
        settings();

        ~settings();

        settings(const settings &e) = delete;

        settings &operator=(const settings &e) = delete;

        void init();

        unsigned int mWindowWidth;
        unsigned int mWindowHeight;
        config::json_config *mConfig;
    };
}

#endif //CITY_DEFENCE_CONFIG_H
