//
// Created by Rob Hendriks on 14/10/2016.
//

#include <stdio.h>
#include <memory>
#include <exception>
#include "engine.h"
#include "../math/box2.hpp"

namespace game {
    void engine::setActiveGUI(gui::base_gui* gui) {
        m_gui = gui;
    }

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

        while (m_running) {
            SDL_Event event;
            while (SDL_PollEvent(&event) != 0) {
                update(&event);
            }
            render();
        }
    }

    void engine::update(SDL_Event *event) {
        if (event->type == SDL_QUIT) {
            m_running = false;
        }
    }

    void engine::render() {
        m_display->clear();

        // TODO: Render items
        if(this->m_gui != nullptr)
            this->m_gui->render(m_display->get_renderer());
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
