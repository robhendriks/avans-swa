//
// Created by robbie on 9-12-2016.
//

#ifndef CITY_DEFENCE_CLI_H
#define CITY_DEFENCE_CLI_H

#include "../../domain/drawable/draw_managers_wrapper.h"
#include "base_view.h"
#include "../../engine/input/mouse_buttons.h"
#include "../../engine/events/mouse_button_down.h"
#include "../../engine/events/key_down.h"
#include "../../engine/input/input_handler.h"
#include "top_bar.h"

namespace gui {
    namespace views {
        class top_bar;
    }
}

namespace gui {
    namespace views {
        class cli : public base_view,
                     engine::eventbus::subscriber<engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT>>,
                     engine::eventbus::subscriber<engine::events::key_down> {
            friend class in_game_menu;
        public:
            cli(top_bar &top_bar1);

            void toggle_show();

            void before();

            void on_display_change(engine::math::box2_t display_box);

            void draw(unsigned int time_elapsed, engine::math::box2_t display_box);

            void after();

            void on_event(engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT> &event);

            void on_event(engine::events::key_down &event);

        private:
            void input_changed();

            TTF_Font *m_font;
            SDL_Texture *m_texture;

            std::string m_input;
            top_bar &m_top_bar;
            bool m_show;
            std::unique_ptr<engine::math::box2_t> m_box;
        };
    }
}

#endif //CITY_DEFENCE_CLI_H
