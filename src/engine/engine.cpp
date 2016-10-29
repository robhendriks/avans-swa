//
// Created by Rob Hendriks on 19/10/2016.
//

#include "engine.h"
#include "settings.h"
#include "input/input_handler.h"
#include "eventbus/eventbus.h"
#include "events/window_cleared.h"

namespace engine {
    const int TICKS_PER_SECOND = 25;
    const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
    const int MAX_FRAMESKIP = 5;

    void engine::warmup() {
        try {
            settings::get();

            init_sdl();
            create_window();
        } catch (std::runtime_error &e) {
            fprintf(stderr, "%s\n", e.what());
            return;
        }
    }

    void engine::run() {
        m_running = true;
        loop();
    }

    void engine::loop() {
        printf("[DEBUG] Starting router loop...\n");

        auto next_game_tick = SDL_GetTicks();
        int loops;
        float interpolation;
        while (m_running) {
            loops = 0;
            while(SDL_GetTicks() > next_game_tick && loops < MAX_FRAMESKIP) {
                update(); // Update the router state

                next_game_tick += SKIP_TICKS;
                loops++;
            }

            m_window->clear();

            interpolation = float(SDL_GetTicks() + SKIP_TICKS - next_game_tick) / float(SKIP_TICKS);

            // Fire event clear event
            auto *clear_event = new events::window_cleared(interpolation);
            eventbus::eventbus<events::window_cleared>::get_instance().fire(*clear_event);
            delete clear_event;

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
                stop();
            }

            // Update the input handler
            input::input_handler::get_instance()->update(event);
        }
    }

    void engine::stop() {
        m_running = false;
    }

    void engine::quit() {
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

    texture::texture_manager &engine::get_texture_manager() {
        auto *manager = new texture::texture_manager(*m_window->get_renderer());

        return *manager;
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
