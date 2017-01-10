//
// Created by robbie on 9-12-2016.
//

#ifndef CITY_DEFENCE_CLI_H
#define CITY_DEFENCE_CLI_H

#include <deque>

#include "../../domain/drawable/draw_managers_wrapper.h"
#include "base_view.h"
#include "../../engine/input/mouse_buttons.h"
#include "../../engine/events/mouse_button_down.h"
#include "../../engine/events/key_down.h"
#include "../../engine/input/input_handler.h"
#include "top_bar.h"
#include "../../utils/string_utils.h"

namespace gui {
    namespace views {
        class top_bar;
    }
}

namespace gui {
    namespace views {
        class cli_item {
        public:
            cli_item(std::string &text, SDL_Texture *texture, engine::math::vec2_t &size);

            std::string get_text() const;

            SDL_Texture *get_texture() const;

            engine::math::vec2_t get_size() const;

        private:
            std::string m_text;
            SDL_Texture *m_texture;
            engine::math::vec2_t m_size;
        };

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
            SDL_Texture *input_metrics(const std::string &text, engine::math::vec2_t &size);

            void input_reset();

            void input_backspace();

            void input_changed();

            void input_parse();

            void submit();

            void message(std::string message);

            top_bar &m_top_bar;
            bool m_show;
            std::unique_ptr<engine::math::box2_t> m_box;

            std::string m_input;
            TTF_Font *m_input_font;
            int m_input_height;
            SDL_Texture *m_input_texture;
            engine::math::vec2_t m_input_size;
            std::deque<cli_item> m_items;
        };
    }
}

#endif //CITY_DEFENCE_CLI_H
