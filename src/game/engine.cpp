//
// Created by Rob Hendriks on 19/10/2016.
//

#include "engine.h"
#include "settings.h"
#include "input/input_handler.h"

namespace game {
    const int TICKS_PER_SECOND = 25;
    const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
    const int MAX_FRAMESKIP = 5;

    engine &engine::get() {
        static engine instance;
        return instance;
    }

    void engine::set_active_gui(gui::base_gui* gui) {
        m_active_gui = gui;
    }

    void engine::run() {
        try {
            settings::get();

            init_sdl();
            create_window();

            // TODO: Load game objects

        } catch (std::runtime_error &e) {
            fprintf(stderr, "%s\n", e.what());
            return;
        }

        loop();
    }

    void engine::loop() {
        printf("[DEBUG] Starting game loop...\n");

        m_running = true;

        auto next_game_tick = SDL_GetTicks();
        int loops;
        float interpolation;
        while (m_running) {
            loops = 0;
            while(SDL_GetTicks() > next_game_tick && loops < MAX_FRAMESKIP) {
                update(); // Update the game state

                next_game_tick += SKIP_TICKS;
                loops++;
            }

            m_window->clear();

            interpolation = float(SDL_GetTicks() + SKIP_TICKS - next_game_tick) / float(SKIP_TICKS);
            render(interpolation); // Display the game

            m_window->present();
        }

        quit();
    }

    void engine::update() {
        // Handle the SDL events
        SDL_Event event;
        while (SDL_PollEvent(&event) != 0) {
            // Check for the QUIT event
            if (event.type == SDL_QUIT) {
                m_running = false;
            }

            // Update the input handler
            input::input_handler::get_instance()->update(event);
        }
    }

    void engine::render(float interpolation) {
        if (this->m_active_gui != nullptr) {
            this->m_active_gui->render(m_window->get_renderer());
        }
    }

    void engine::quit() {
        printf("[DEBUG] Cleaning up...\n");

        // TODO: Clean up game objects

        // Destroy the window if it was created
        if (m_window) {
            m_window->destroy();
            delete m_window;
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
        if (!m_window) {
            window_config cfg;
            cfg.title = "City Defence";

            settings *s = &settings::get();
            cfg.w = s->get_window_width();
            cfg.h = s->get_window_height();

            m_window = new window(cfg);
            m_window->create();
        }
    }
}
