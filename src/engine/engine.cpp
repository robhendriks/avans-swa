//
// Created by Rob Hendriks on 19/10/2016.
//

#include "engine.h"
#include "input/input_handler.h"
#include "eventbus/eventbus.h"
#include "events/window_cleared.h"

namespace engine {
    engine::engine(engine_config config) : m_window(nullptr), m_config(config) {
    }

    void engine::warmup() {
        try {
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
            while(SDL_GetTicks() > next_game_tick && loops < m_config.max_frameskip) {
                update(); // Update the router state

                next_game_tick += m_config.get_skip_ticks();
                loops++;
            }

            m_window->clear();

            interpolation = float(SDL_GetTicks() + m_config.get_skip_ticks() - next_game_tick) / float(m_config.get_skip_ticks());

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

    texture::texture_manager *engine::get_texture_manager() const {
        return new texture::texture_manager(*m_window->get_renderer());
    }

    void engine::create_window() {
        // Create the window of it wasn't already created
        if (m_window == nullptr) {
            m_window = new window(m_config.win_config);
            m_window->create();
        }
    }

    window *engine::get_window() const {
        return m_window;
    }
}