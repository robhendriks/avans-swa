//
// Created by Rob Hendriks on 14/10/2016.
//

#include <stdio.h>
#include <memory>
#include <exception>
#include "engine.h"
#include "../math/box2.hpp"
#include "input/input_handler.h"

namespace game {
    const int TICKS_PER_SECOND = 25;
    const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
    const int MAX_FRAMESKIP = 5;

    void engine::load_config() {
        m_config = std::make_shared<config::ini_config>(CONFIG_PATH);
        if (!m_config->load()) {
            throw std::runtime_error("Unable to load configuration");
        }
    }

    void engine::init_display() {
        int x, y, w, h;
        x = SDL_WINDOWPOS_CENTERED;
        y = SDL_WINDOWPOS_CENTERED;
        w = m_config->get_long("window", "width", DISPLAY_WIDTH);
        h = m_config->get_long("window", "height", DISPLAY_HEIGHT);

        m_display = std::make_shared<graphics::display>();
        if (!m_display->create(DISPLAY_TITLE, x, y, w, h)) {
            throw std::runtime_error(SDL_GetError());
        }
    }

    void engine::init() {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            printf("Failed to initialize SDL: %s\n", SDL_GetError());
            return;
        }

        try {
            load_config();
            init_display();

            // TODO: Load resources
        } catch (std::runtime_error &e) {
            printf("Failed to initialize engine: %s\n", e.what());
            return;
        }

        loop();
    }

    void engine::loop() {
        if (m_running) {
            return; // Already running
        }

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

            interpolation = float(SDL_GetTicks() + SKIP_TICKS - next_game_tick) / float(SKIP_TICKS);
            render(interpolation); // Display the game
        }
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
        m_display->clear();

        // TODO: Render items

        m_display->present();
    }

    void engine::destroy() {
        m_display->destroy();

        SDL_Quit();
    }

    const int engine::DISPLAY_WIDTH = 1280;
    const int engine::DISPLAY_HEIGHT = 720;
    const char *engine::DISPLAY_TITLE = "City Defence";
    const char *engine::CONFIG_PATH = "config.ini";
}
