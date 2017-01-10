//
// Created by robbie on 9-12-2016.
//

#include "cli.h"
#include "../../engine/graphics/box_builder.h"

namespace gui {
    namespace views {

        cli::cli(top_bar &top_bar1) : m_top_bar(top_bar1), m_show(false), m_font(nullptr), m_texture(nullptr) {}

        void cli::before() {
            m_show = false;

            m_font = m_top_bar.m_font_manager.get_font("roboto", 12);

            auto &eventbus = engine::eventbus::eventbus::get_instance();
            eventbus.subscribe(dynamic_cast<engine::eventbus::subscriber<engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT>>*>(this));
            eventbus.subscribe(dynamic_cast<engine::eventbus::subscriber<engine::events::key_down>*>(this));
        }

        void cli::on_display_change(engine::math::box2_t display_box) {
            engine::graphics::box_builder builder1(engine::math::vec2_t{display_box.size().x, 128});
            builder1.as_left_top(m_top_bar.m_bar_box->left_bottom());
            m_box.reset(new engine::math::box2_t(builder1.build()));
        }

        void cli::draw(unsigned int time_elapsed, engine::math::box2_t display_box) {
            if (m_show) {
                m_top_bar.m_color_manager.draw({0, 0, 0, 128}, *m_box);
                m_top_bar.m_texture_manager.draw(m_texture, *m_box);
            }
        }

        void cli::on_event(engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT> &event) {
            auto *position = engine::input::input_handler::get_instance()->get_mouse_position();

            // TODO
        }

        void cli::on_event(engine::events::key_down &event) {
            if (!m_show) {
                return;
            }

            auto kc = event.get_keycode();

            if (kc == engine::input::keycodes::keycode::ESCAPE) {
                toggle_show();
            } else if (engine::input::keycodes::is_input_keycode(kc)) {
                char c = engine::input::keycodes::keycode_to_char(kc);

                if (c != '\0') {
                    m_input += c;
                    input_changed();
                }
            } else if (kc == engine::input::keycodes::BACKSPACE && m_input.size() > 0) {
                m_input = m_input.substr(0, m_input.size() - 1);
                input_changed();
            }
        }

        void cli::after() {
            SDL_DestroyTexture(m_texture);
            TTF_CloseFont(m_font);

            m_texture = nullptr;
            m_font = nullptr;

            auto &eventbus = engine::eventbus::eventbus::get_instance();
            eventbus.unsubscribe(dynamic_cast<engine::eventbus::subscriber<engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT>>*>(this));
            eventbus.unsubscribe(dynamic_cast<engine::eventbus::subscriber<engine::events::key_down>*>(this));
        }

        void cli::toggle_show() {
            m_show = !m_show;
        }

        void cli::input_changed() {
            m_texture = m_top_bar.m_texture_manager.load_text(m_input, {255, 255, 255, 255}, *m_font, "cli_input");

            SDL_Log("%s\n", m_input.c_str());
        }
    }
}
