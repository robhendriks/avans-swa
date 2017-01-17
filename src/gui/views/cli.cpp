//
// Created by robbie on 9-12-2016.
//

#include "cli.h"
#include "../../engine/graphics/box_builder.h"

namespace gui {
    namespace views {

        cli_item::cli_item(std::string &text, SDL_Texture *texture, engine::math::vec2_t &size) : m_text(text), m_texture(texture), m_size(size) {}

        cli_item::~cli_item() {
            if (m_texture) {
                SDL_DestroyTexture(m_texture);
            }
        }

        std::string cli_item::get_text() const {
            return m_text;
        }

        SDL_Texture *cli_item::get_texture() const {
            return m_texture;
        }

        engine::math::vec2_t cli_item::get_size() const {
            return m_size;
        }

        cli::cli(top_bar &top_bar1)
            : m_top_bar(top_bar1), m_show(false), m_input_font(nullptr), m_input_texture(nullptr), m_input_size(0, 0),
              m_command_manager(new utils::command_manager), m_in_game_menu(nullptr) {

            m_command_manager->add("god", "god", [this](const utils::params &params) -> bool {
                if (m_in_game_menu) {
                    if (m_in_game_menu->m_main_map_controller->get_game_world()->get_current_level()->execute_cheat()) {
                        message("Godmode enabled.");
                    } else {
                        message("Godmode disabled.");
                    }
                    return true;
                }
                return false;
            });

            m_command_manager->add("exit", "exit", [this](const utils::params &params) -> bool {
                toggle_show();
                return true;
            });

            /*m_command_manager->add("gold", "gold <amount>", [this](const utils::params &params) -> bool {
                if (params.size() < 2) {
                    return false;
                }
                std::stringstream ss;
                ss << "Got " << params[1] << " gold?";
                message(ss.str());
                return true;
            });*/
        }

        void cli::before() {
            m_show = false;

            m_input_font = m_top_bar.m_font_manager.get_font("roboto", 14);
            m_input_height = TTF_FontHeight(m_input_font);

            auto &eventbus = engine::eventbus::eventbus::get_instance();
            eventbus.subscribe(dynamic_cast<engine::eventbus::subscriber<engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT>>*>(this));
            eventbus.subscribe(dynamic_cast<engine::eventbus::subscriber<engine::events::key_down>*>(this));
        }

        void cli::on_display_change(engine::math::box2_t display_box) {}

        void cli::draw(unsigned int time_elapsed, engine::math::box2_t display_box) {
            if (m_show) {
                size_t count = m_items.size() + 1;
                size_t i = 0;

                engine::graphics::box_builder builder(engine::math::vec2_t{display_box.size().x, static_cast<float>(count * m_input_height)});
                builder.as_left_top(m_top_bar.m_bar_box->left_bottom());
                m_box.reset(new engine::math::box2_t(builder.build()));

                m_top_bar.m_color_manager.draw({0, 0, 0, 80}, *m_box);

                engine::math::box2_t item_box{0, 0, 0, 0};

                for (auto &item : m_items) {
                    item_box.min = m_box->min + engine::math::vec2_t{0, static_cast<float>(i * m_input_height)};
                    item_box.max = item_box.min + item.get_size();

                    m_top_bar.m_texture_manager.draw(item.get_texture(), item_box);
                    i++;
                }

                item_box.min = m_box->min + engine::math::vec2_t{0, static_cast<float>(i * m_input_height)};
                item_box.max = item_box.min + m_input_size;

                m_top_bar.m_texture_manager.draw(m_input_texture, item_box);
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
                m_input = "";
                input_changed();
            } else if (engine::input::keycodes::is_input_keycode(kc) && m_input.size() < 100) {
                char c = engine::input::keycodes::keycode_to_char(kc);

                if (c != '\0') {
                    m_input += c;
                    input_changed();
                }
            } else if (kc == engine::input::keycodes::BACKSPACE && m_input.size() > 0) {
                input_backspace();
            } else if (kc == engine::input::keycodes::ENTER) {
                submit();
            }
        }

        void cli::after() {
//            if (m_input_texture) {
//                SDL_DestroyTexture(m_input_texture);
//                m_input_texture = nullptr;
//            }
//            if (m_input_font) {
//                TTF_CloseFont(m_input_font);
//                m_input_font = nullptr;
//            }
//
            input_reset();
            m_items.clear();

            auto &eventbus = engine::eventbus::eventbus::get_instance();
            eventbus.unsubscribe(dynamic_cast<engine::eventbus::subscriber<engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT>>*>(this));
            eventbus.unsubscribe(dynamic_cast<engine::eventbus::subscriber<engine::events::key_down>*>(this));
        }

        void cli::toggle_show() {
            m_show = !m_show;

            if (!m_show) {
                m_items.clear();
                input_reset();
            }
        }

        SDL_Texture *cli::input_metrics(const std::string &text, engine::math::vec2_t &size) {
            int w, h;
            TTF_SizeText(m_input_font, text.c_str(), &w, &h);

            size.x = static_cast<float>(w);
            size.y = static_cast<float>(h);

            return m_top_bar.m_texture_manager.load_text(text, {200, 200, 200, 255}, *m_input_font, "cli_input");
        }

        void cli::input_changed() {
            m_input_texture = input_metrics(m_input, m_input_size);
        }

        void cli::input_reset() {
            m_input = "";
            input_changed();
        }

        void cli::input_backspace() {
            if (m_input.size() > 0) {
                m_input = m_input.substr(0, m_input.size() - 1);
                input_changed();
            }
        }

        void cli::submit() {
            if (m_items.size() >= 10) {
                m_items.pop_front();
            }
            m_items.emplace_back(m_input, m_input_texture, m_input_size);

            input_parse();
            input_reset();
        }

        void cli::input_parse() {
            try {
                m_command_manager->execute(utils::string_utils::tokenize(m_input, " "));
            } catch (std::exception &e) {
                message(std::string(e.what()));
            }
        }

        void cli::message(std::string message) {
            engine::math::vec2_t size{0, 0};
            SDL_Texture *texture = input_metrics(message, size);

            if (m_items.size() >= 10) {
                m_items.pop_front();
            }
            m_items.emplace_back(message, texture, size);
        }

        void cli::set_in_game_menu(const std::shared_ptr<in_game_menu> &in_game_menu1) {
            m_in_game_menu = in_game_menu1;
        }
    }
}
