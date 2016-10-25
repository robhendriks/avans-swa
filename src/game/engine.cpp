//
// Created by Rob Hendriks on 19/10/2016.
//

#include "engine.h"
#include "settings.h"

namespace game {
    engine &engine::get() {
        static engine instance;
        return instance;
    }

    void engine::setActiveGUI(gui::base_gui* gui) {
        mActiveGUI = gui;
    }

    void engine::run() {
        try {
            settings::get();

            init_sdl();
            create_window();

            // TODO: Load game objects
            if(this->mActiveGUI != nullptr)
                this->mActiveGUI->render(mWindow->get_renderer());

        } catch (std::runtime_error &e) {
            fprintf(stderr, "%s\n", e.what());
            return;
        }

        loop();
    }

    void engine::loop() {
        printf("[DEBUG] Starting game loop...\n");

        bool done = false;

        while (!done) {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    done = true;
                }
            }

            mWindow->clear();

            // TODO: Render game objects

            mWindow->present();
        }

        quit();
    }

    void engine::quit() {
        printf("[DEBUG] Cleaning up...\n");

        // TODO: Clean up game objects

        // Destroy the window if it was created
        if (mWindow) {
            mWindow->destroy();
            delete mWindow;
        }
    }

    void engine::init_sdl() {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            std::string error = SDL_GetError();
            throw std::runtime_error("Failed to initialize SDL: " + error);
        }
    }

    void engine::create_window() {
        // Create the window of it wasn't already created
        if (!mWindow) {
            window_config cfg;
            cfg.title = "City Defence";

            settings *s = &settings::get();
            cfg.w = s->get_window_width();
            cfg.h = s->get_window_height();

            mWindow = new window(cfg);
            mWindow->create();
        }
    }
}
