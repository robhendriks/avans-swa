//
// Created by Rob Hendriks on 19/10/2016.
//

#include "settings.h"

namespace engine {
    settings::settings() : mConfig(new config::json_config("config.json")) {
        init();
    }

    settings::~settings() {}

    settings &settings::get() {
        static settings instance;
        return instance;
    }

    void settings::init() {
        // Load config
        mConfig->load();

        // Set default values
        mWindowWidth = 800;
        mWindowHeight = 600;

        // Set values from JSON
        json jRoot = mConfig->get_json();
        json jWindow = jRoot["window"];

        if (jWindow.is_object()) {
            json jWidth = jWindow["width"];
            json jHeight = jWindow["height"];

            if (jWidth.is_number_unsigned()) {
                mWindowWidth = jWidth;
            }
            if (jHeight.is_number_unsigned()) {
                mWindowHeight = jHeight;
            }
        }
    }

    unsigned int settings::get_window_width() const {
        return mWindowWidth;
    }

    unsigned int settings::get_window_height() const {
        return mWindowHeight;
    }
}
