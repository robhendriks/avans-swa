//
// Created by robbie on 5-11-2016.
//

#include "game.h"

game::game(engine::window &window) : m_window(window), m_current_view(nullptr) {

}

void game::set_view(gui::views::base_view &view) {
    // Only set the view when it is different
    if (m_current_view != &view) {
        if (m_current_view != nullptr) {
            m_current_view->after();
        }

        m_current_view = &view;
        m_current_view->before();

        m_current_view->layout({0, 0, 1280, 720});
    }
}

void game::update() {
    if (!m_current_view) {
        return;
    }

    // TODO: more stuff
}

void game::draw() {
    if (!m_current_view) {
        return;
    }
    m_current_view->draw(0, {0, 0, 1280, 720});

    // TODO: more stuff
}
