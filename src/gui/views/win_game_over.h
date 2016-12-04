//
// Created by te on 19-Nov-16.
//

#ifndef CITY_DEFENCE_WIN_GAME_OVER_H
#define CITY_DEFENCE_WIN_GAME_OVER_H

#include "base_view.h"
#include "level_goals.h"
#include "../../engine/graphics/moveable_box.h"
#include "../controllers/main_map_controller.h"
#include "../models/transition_level_model.h"
#include <memory>

namespace gui {
    namespace controllers {
        class main_map_controller;
    }
}

namespace gui {
    namespace views {
        class top_bar;
    }
}

namespace gui {
    namespace views {
        class win_game_over
            : public base_view,
              engine::eventbus::subscriber<engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT>> {
        public:
            win_game_over(top_bar &top_bar1, level_goals &goals_view, models::transition_level_model &model,
                engine::audio::sound_manager &sound_manager);

            void before();

            void on_display_change(engine::math::box2_t display_box);

            void after();

            void draw(unsigned int time_elapsed, engine::math::box2_t display_box);

            void on_event(engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT> &event);

            void set_controller(gui::controllers::main_map_controller &controller);

        private:
            top_bar &m_top_bar;
            level_goals &m_goals_view;
            gui::controllers::main_map_controller *m_controller;
            models::transition_level_model &m_model;
            engine::audio::sound_manager &m_sound_manager;
            std::unique_ptr<engine::math::box2_t> m_title_box;
            std::unique_ptr<engine::math::box2_t> m_continue_box;
            std::unique_ptr<engine::math::box2_t> m_continue_text_box;
            std::unique_ptr<engine::math::box2_t> m_continue_slider_box;
            std::unique_ptr<engine::graphics::moveable_box> m_moveable_slider_box;
        };
    }
}

#endif //CITY_DEFENCE_WIN_GAME_OVER_H
