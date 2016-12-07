//
// Created by te on 25-Oct-16.
//

#include "main_menu.h"
#include "../../engine/graphics/box_builder.h"

namespace gui {
    namespace views {
        main_menu::main_menu(top_bar &top_bar1, engine::audio::music_manager &music_manager,
                             engine::audio::sound_manager &sound_manager)
            : m_top_bar(top_bar1), m_music_manager(music_manager), m_sound_manager(sound_manager) {}

        void main_menu::before() {
            m_top_bar.before();

            // Load textures
            m_top_bar.m_texture_manager.load("images/logo.png", "logo");
            m_top_bar.m_texture_manager.load_from_svg("images/ui-pack.svg", {{1261, 244}, {1451, 289}}, 1.5, "blue_btn");
            m_top_bar.m_texture_manager.load_from_svg("images/ui-pack.svg", {{1261, 64}, {1451, 110}}, 1.5, "yellow_btn");
            m_top_bar.m_texture_manager.load_from_svg("images/ui-pack.svg", {{1261, 184}, {1451, 229}}, 1.5, "red_btn");

            m_top_bar.m_texture_manager.load_from_svg("images/ui-pack.svg", {{1007, 570}, {1046, 601}}, 1, "green_slider_left");
            m_top_bar.m_texture_manager.load_from_svg("images/ui-pack.svg", {{1080, 570}, {1119, 601}}, 1, "green_slider_right");

            // Load (and play) music
            m_music_manager.load("sounds/menu.wav", "menu_bg_music");
            m_music_manager.play("menu_bg_music");

            // Load sound effects
            m_sound_manager.load("sounds/menu_rollover.wav", "menu_rollover");

            // Load the menu texts
            m_top_bar.m_texture_manager.load_text("Play", {0, 0, 0}, *m_top_bar.m_font_manager.get_font("roboto", 46), "m_t_play");
            m_top_bar.m_texture_manager.load_text("Load", {0, 0, 0}, *m_top_bar.m_font_manager.get_font("roboto", 46), "m_t_load");
            m_top_bar.m_texture_manager.load_text("Credits", {0, 0, 0}, *m_top_bar.m_font_manager.get_font("roboto", 46), "m_t_credits");

            auto &eventbus = engine::eventbus::eventbus::get_instance();
            eventbus.subscribe(dynamic_cast<engine::eventbus::subscriber<engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT>>*> (this));
            eventbus.subscribe(dynamic_cast<engine::eventbus::subscriber<engine::events::mouse_motion>*> (this));
            eventbus.subscribe(dynamic_cast<engine::eventbus::subscriber<engine::events::key_down>*> (this));
        }

        void main_menu::on_display_change(engine::math::box2_t display_box) {
            m_top_bar.on_display_change(display_box);

            // Create the logo box
            engine::graphics::box_builder builder1(m_top_bar.m_texture_manager.get_size("logo"));
            builder1.as_left_top(m_top_bar.m_bar_box->left_bottom()).add_margin({0, 50})
                .center_horizontal(m_top_bar.m_bar_box->min.x, m_top_bar.m_bar_box->max.x);
            m_logo_box.reset(new engine::math::box2_t(builder1.build()));

            auto menu_btn_size = engine::math::vec2_t({380, 90});
            // Create the play btn box
            engine::graphics::box_builder builder2(menu_btn_size);
            builder2.as_left_top(m_logo_box->left_bottom()).add_margin({0, 100})
                .center_horizontal(m_logo_box->min.x, m_logo_box->max.x);
            m_play_btn_box.reset(new engine::math::box2_t(builder2.build()));

            // Create the play text box
            engine::graphics::box_builder builder3(m_top_bar.m_texture_manager.get_size("m_t_play"));
            builder3.to_center(*m_play_btn_box);
            m_play_text_box.reset(new engine::math::box2_t(builder3.build()));

            // Create the load btn box
            builder2.add_margin({0, menu_btn_size.y + 50});
            m_load_btn_box.reset(new engine::math::box2_t(builder2.build()));

            // Create the load text box
            engine::graphics::box_builder builder4(m_top_bar.m_texture_manager.get_size("m_t_load"));
            builder4.to_center(*m_load_btn_box);
            m_load_text_box.reset(new engine::math::box2_t(builder4.build()));

            // Create the credits btn box
            builder2.add_margin({0, menu_btn_size.y + 50});
            m_credits_btn_box.reset(new engine::math::box2_t(builder2.build()));

            // Create the credits text box
            engine::graphics::box_builder builder5(m_top_bar.m_texture_manager.get_size("m_t_credits"));
            builder5.to_center(*m_credits_btn_box);
            m_credits_text_box.reset(new engine::math::box2_t(builder5.build()));

            // Set slider possible positions
            m_slider_positions.clear();
            m_slider_positions.push_back(*m_play_btn_box);
            m_slider_positions.push_back(*m_load_btn_box);
            m_slider_positions.push_back(*m_credits_btn_box);

            if (m_slider_left_box == nullptr || m_slider_right_box == nullptr) {
                set_sliders(0, true);
            }
        }

        void main_menu::draw(unsigned int time_elapsed, engine::math::box2_t display_box) {
            m_top_bar.draw(time_elapsed, display_box);

            // Draw the logo
            m_top_bar.m_texture_manager.draw("logo", *m_logo_box);

            // Draw the play btn
            m_top_bar.m_texture_manager.draw("blue_btn", *m_play_btn_box);
            m_top_bar.m_texture_manager.draw("m_t_play", *m_play_text_box);

            // Draw the load btn
            m_top_bar.m_texture_manager.draw("red_btn", *m_load_btn_box);
            m_top_bar.m_texture_manager.draw("m_t_load", *m_load_text_box);

            // Draw the credits btn
            m_top_bar.m_texture_manager.draw("yellow_btn", *m_credits_btn_box);
            m_top_bar.m_texture_manager.draw("m_t_credits", *m_credits_text_box);

            // Draw the sliders
            m_top_bar.m_texture_manager.draw("green_slider_right", *m_slider_left_box);
            m_top_bar.m_texture_manager.draw("green_slider_left", *m_slider_right_box);
        }

        void main_menu::on_event(engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT> &event) {
            engine::math::vec2_t *position = engine::input::input_handler::get_instance()->get_mouse_position();

            menu_btn_click(*position);
        }

        void main_menu::menu_btn_click(engine::math::vec2_t mouse_pos) {
            if (m_play_btn_box->contains(mouse_pos)) {
                m_top_bar.m_menu_controller->play();
            } else if (m_load_btn_box->contains(mouse_pos)) {
                m_top_bar.m_menu_controller->load();
            } else if (m_credits_btn_box->contains(mouse_pos)) {
                m_top_bar.m_menu_controller->credits();
            }
        }

        void main_menu::on_event(engine::events::key_down &event) {
            auto keycode = event.get_keycode();

            switch (keycode) {
                case engine::input::keycodes::UP :
                    set_sliders(m_current_slider_pos - 1);
                    break;
                case engine::input::keycodes::DOWN :
                    set_sliders(m_current_slider_pos + 1);
                    break;
                case engine::input::keycodes::ENTER :
                    menu_btn_click(m_slider_positions[m_current_slider_pos].center());
                    break;
                default:
                    return;
            }
        }

        void main_menu::on_event(engine::events::mouse_motion &event) {
            auto position = event.get_mouse_position();

            for (size_t i = 0; i < m_slider_positions.size(); i++) {
                if (m_slider_positions[i].contains(position)) {
                    set_sliders(i);
                }
            }
        }

        void main_menu::set_sliders(unsigned int pos, bool force) {
            if (pos < m_slider_positions.size() && (pos != m_current_slider_pos || force)) {
                auto box = m_slider_positions[pos];

                // Create the left slider box
                engine::graphics::box_builder builder1(m_top_bar.m_texture_manager.get_size("green_slider_right"));
                builder1.as_right_top(box.left_top())
                    .center_vertical(box.min.y, box.max.y).add_margin({-20, 0});
                m_slider_left_box.reset(new engine::math::box2_t(builder1.build()));

                // Create the right slider box
                engine::graphics::box_builder builder2(m_top_bar.m_texture_manager.get_size("green_slider_left"));
                builder2.as_left_top(box.right_top())
                    .center_vertical(box.min.y, box.max.y).add_margin({20, 0});
                m_slider_right_box.reset(new engine::math::box2_t(builder2.build()));

                m_current_slider_pos = pos;

                // Play sound effect
                m_sound_manager.play("menu_rollover");
            }
        }

        void main_menu::after() {
            m_top_bar.after();

            // Unload textures
            m_top_bar.m_texture_manager.unload("logo");
            m_top_bar.m_texture_manager.unload("blue_btn");
            m_top_bar.m_texture_manager.unload("yellow_btn");
            m_top_bar.m_texture_manager.unload("red_btn");
            m_top_bar.m_texture_manager.unload("green_slider_left");
            m_top_bar.m_texture_manager.unload("green_slider_right");

            // Unload music
            m_music_manager.unload("menu_bg_music");

            // Unload sound
            m_sound_manager.unload("menu_rollover");

            // Unload texts
            m_top_bar.m_texture_manager.unload("m_t_play");
            m_top_bar.m_texture_manager.unload("m_t_load");
            m_top_bar.m_texture_manager.unload("m_t_credits");

            auto &eventbus = engine::eventbus::eventbus::get_instance();
            eventbus.unsubscribe(dynamic_cast<engine::eventbus::subscriber<engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT>>*> (this));
            eventbus.unsubscribe(dynamic_cast<engine::eventbus::subscriber<engine::events::mouse_motion>*> (this));
            eventbus.unsubscribe(dynamic_cast<engine::eventbus::subscriber<engine::events::key_down>*> (this));
        }

        void main_menu::set_controller(std::shared_ptr<controllers::menu_controller> menu_controller) {
            m_top_bar.set_controller(menu_controller);
        }
    }
}
