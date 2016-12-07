//
// Created by robbie on 7-12-2016.
//

#ifndef CITY_DEFENCE_IN_GAME_MENU_H
#define CITY_DEFENCE_IN_GAME_MENU_H

#include "base_view.h"
#include "../../engine/input/mouse_buttons.h"
#include "../../engine/events/mouse_button_down.h"
#include "top_bar.h"
#include <memory>

namespace gui {
    namespace views {
        class top_bar;
    }
}

namespace gui {
    namespace views {
        class in_game_menu : public base_view,
                             engine::eventbus::subscriber<engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT>>,
                             engine::eventbus::subscriber<engine::events::key_down> {
            friend class level;
            friend class win_game_over;
        public:
            in_game_menu(top_bar &top_bar1);

            void before();

            void on_display_change(engine::math::box2_t display_box);

            void draw(unsigned int time_elapsed, engine::math::box2_t display_box);

            void after();

            void on_event(engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT> &event);

            void on_event(engine::events::key_down &event);

            void call_on_show_change(std::function<void(bool)> callback);

        private:
            void change_show();

            top_bar &m_top_bar;
            bool m_show;
            std::unique_ptr<engine::math::box2_t> m_menu_icon_box;
            std::unique_ptr<engine::math::box2_t> m_overlay_box;
            std::unique_ptr<engine::math::box2_t> m_menu_box;
            std::unique_ptr<engine::math::box2_t> m_save_btn_box;
            std::unique_ptr<engine::math::box2_t> m_save_btn_text_box;
            std::unique_ptr<engine::math::box2_t> m_back_btn_box;
            std::unique_ptr<engine::math::box2_t> m_back_btn_text_box;
            std::unique_ptr<engine::math::box2_t> m_quit_btn_box;
            std::unique_ptr<engine::math::box2_t> m_quit_btn_text_box;
            std::vector<std::function<void(bool)>> m_callbacks;
        };
    }
}

#endif //CITY_DEFENCE_IN_GAME_MENU_H
