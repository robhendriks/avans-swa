//
// Created by robbie on 9-1-2017.
//

#include "load.h"

namespace gui {
    namespace views {

        load::load(top_bar &top_bar1, models::load_model &load_model) :
            m_top_bar(top_bar1), m_load_model(load_model), m_load_controller(nullptr) {

        }

        void load::before() {
            m_top_bar.before();

            // Subscribe on click event
            engine::eventbus::eventbus::get_instance().subscribe(this);
        }

        void load::on_display_change(engine::math::box2_t display_box) {
            m_top_bar.on_display_change(display_box);
        }

        void load::draw(unsigned int time_elapsed, engine::math::box2_t display_box) {
            m_top_bar.draw(time_elapsed, display_box);
        }

        void load::after() {
            m_top_bar.after();

            // Unsubscribe on click event
            engine::eventbus::eventbus::get_instance().unsubscribe(this);
        }

        void load::on_event(engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT> &event) {
            // Just for now
            if (m_load_model.saved_games.size() > 0) {
                m_load_controller->load(*m_load_model.saved_games.front());
            }
        }

        void load::set_load_controller(controllers::load_controller &load_controller) {
            m_load_controller = &load_controller;
        }
    }
}
