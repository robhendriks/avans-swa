//
// Created by robbie on 9-1-2017.
//

#ifndef CITY_DEFENCE_LOAD_H
#define CITY_DEFENCE_LOAD_H

#include "base_view.h"
#include "top_bar.h"
#include "../controllers/load_controller.h"
#include "../models/load_model.h"

namespace gui {
    namespace controllers {
        class load_controller;
    }
}

namespace gui {
    namespace views {
        class load : public base_view,
            engine::eventbus::subscriber<engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT>> {
        public:
            load(top_bar &top_bar1, models::load_model &load_model);

            void before();

            void on_display_change(engine::math::box2_t display_box);

            void after();

            void draw(unsigned int time_elapsed, engine::math::box2_t display_box);

            void on_event(engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT> &event);

            void set_load_controller(controllers::load_controller &load_controller);

        private:
            top_bar &m_top_bar;
            models::load_model &m_load_model;
            controllers::load_controller *m_load_controller;
        };
    }
}

#endif //CITY_DEFENCE_LOAD_H
