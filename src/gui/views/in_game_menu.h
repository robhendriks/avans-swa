//
// Created by robbie on 7-12-2016.
//

#ifndef CITY_DEFENCE_IN_GAME_MENU_H
#define CITY_DEFENCE_IN_GAME_MENU_H

#include "base_view.h"
#include "top_bar.h"

namespace gui {
    namespace views {
        class in_game_menu : public base_view,
                             engine::eventbus::subscriber<engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT>> {
        public:
            in_game_menu(top_bar &top_bar1);

            void before();

            void on_display_change(engine::math::box2_t display_box);

            void draw(unsigned int time_elapsed, engine::math::box2_t display_box);

            void after();

            void on_event(engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT> &event);

        private:
            top_bar &m_top_bar;
            bool m_show;
            std::unique_ptr<engine::math::box2_t> m_menu_icon_box;
            std::unique_ptr<engine::math::box2_t> m_overlay_box;
        };
    }
}

#endif //CITY_DEFENCE_IN_GAME_MENU_H
