//
// Created by robbie on 5-11-2016.
//

#include "game.h"

game::game(engine::window &window) : m_window(window), m_current_view(nullptr) {

}

void game::use_view(gui::views::base_view &view) {
    // Only set the view when it is different
    if (m_current_view != &view) {
        if (m_current_view != nullptr) {
            m_current_view->after();
        }

        m_current_view = &view;
        m_current_view->before();

        // Let possible objects know about the display screen
        m_window.trigger_display_change();
    }
}

void game::on_event(engine::events::window_cleared &event) {
    m_current_view->draw(event.get_time_elapsed());
}
