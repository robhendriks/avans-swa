//
// Created by robbie on 7-12-2016.
//

#include "in_game_menu.h"
#include "../../engine/graphics/box_builder.h"

namespace gui {
    namespace views {

        in_game_menu::in_game_menu(top_bar &top_bar1) : m_top_bar(top_bar1), m_show(false) {

        }

        void in_game_menu::before() {
            m_top_bar.before();

            // Make sure it's not shown
            m_show = false;

            // Load textures
            m_top_bar.m_texture_manager.load("images/menu_icon.png", "igm_icon");
            m_top_bar.m_texture_manager.load_from_svg("images/ui-pack.svg", {{1261, 184}, {1451, 229}}, 1.5, "igm_red_btn");
            m_top_bar.m_texture_manager.load_from_svg("images/ui-pack.svg", {{1261, 64}, {1451, 110}}, 1.5, "igm_yellow_btn");
            m_top_bar.m_texture_manager.load_from_svg("images/ui-pack.svg", {{1261, 124}, {1451, 169}}, 1.5, "igm_green_btn");
            m_top_bar.m_texture_manager.load_from_svg("images/ui-pack.svg", {{1, 310}, {101, 410}}, 3.5, "igm_grey_panel");
            m_top_bar.m_texture_manager.load_from_svg("images/ui-pack.svg", {{758, 625}, {794, 661}}, 1, "igm_red_circle");
            m_top_bar.m_texture_manager.load_from_svg("images/ui-pack.svg", {{9, 703}, {27, 721}}, 1, "igm_white_cross");

            // Load texts
            m_top_bar.m_texture_manager.load_text("Save", {255, 255, 255},
                                                  *m_top_bar.m_font_manager.get_font("roboto", 25), "igm_save");
            m_top_bar.m_texture_manager.load_text("Back to Main Menu", {255, 255, 255},
                                                  *m_top_bar.m_font_manager.get_font("roboto", 25), "igm_quit");
            m_top_bar.m_texture_manager.load_text("Continue the Game", {255, 255, 255},
                                                  *m_top_bar.m_font_manager.get_font("roboto", 25), "igm_back");

            // Subscribe to events
            auto &eventbus = engine::eventbus::eventbus::get_instance();

            eventbus.subscribe(dynamic_cast<engine::eventbus::subscriber<engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT>>*>(this));
            eventbus.subscribe(dynamic_cast<engine::eventbus::subscriber<engine::events::key_down>*>(this));
        }

        void in_game_menu::on_display_change(engine::math::box2_t display_box) {
            m_top_bar.on_display_change(display_box);

            // Create the menu icon box
            engine::graphics::box_builder builder1(m_top_bar.m_texture_manager.get_size("igm_icon"));
            builder1.as_left_top(m_top_bar.m_bar_box->left_top()).add_margin({5, 0});
            m_menu_icon_box.reset(new engine::math::box2_t(builder1.build()));

            // Create the overlay box
            engine::graphics::box_builder builder2(display_box.size() - engine::math::vec2_t{0, m_top_bar.m_bar_box->height()});
            builder2.as_left_top(m_top_bar.m_bar_box->left_bottom());
            m_overlay_box.reset(new engine::math::box2_t(builder2.build()));

            // Create the menu box
            engine::graphics::box_builder builder3(m_top_bar.m_texture_manager.get_size("igm_grey_panel"));
            builder3.to_center(*m_overlay_box);
            m_menu_box.reset(new engine::math::box2_t(builder3.build()));

            // Create the menu button boxes and text boxes
            auto btn_size = m_top_bar.m_texture_manager.get_size("igm_green_btn");
            auto margin_between_btns = (m_menu_box->height() - btn_size.y * 3) / 4;
            engine::graphics::box_builder builder4(btn_size);
            builder4.as_left_top(m_menu_box->left_top()).center_horizontal(m_menu_box->min.x, m_menu_box->max.x)
                .add_margin({0, margin_between_btns});
            m_save_btn_box.reset(new engine::math::box2_t(builder4.build()));

            engine::graphics::box_builder builder5(m_top_bar.m_texture_manager.get_size("igm_save"));
            builder5.to_center(*m_save_btn_box);
            m_save_btn_text_box.reset(new engine::math::box2_t(builder5.build()));

            builder4.add_margin({0, margin_between_btns + btn_size.y});
            m_back_btn_box.reset(new engine::math::box2_t(builder4.build()));

            engine::graphics::box_builder builder6(m_top_bar.m_texture_manager.get_size("igm_back"));
            builder6.to_center(*m_back_btn_box);
            m_back_btn_text_box.reset(new engine::math::box2_t(builder6.build()));

            builder4.add_margin({0, margin_between_btns + btn_size.y});
            m_quit_btn_box.reset(new engine::math::box2_t(builder4.build()));

            engine::graphics::box_builder builder7(m_top_bar.m_texture_manager.get_size("igm_quit"));
            builder7.to_center(*m_quit_btn_box);
            m_quit_btn_text_box.reset(new engine::math::box2_t(builder7.build()));

            // Create the right top cross
            engine::graphics::box_builder builder8(m_top_bar.m_texture_manager.get_size("igm_red_circle"));
            builder8.as_center(m_menu_box->right_top()).add_margin({-4, 8});
            m_cross_circle_box.reset(new engine::math::box2_t(builder8.build()));

            engine::graphics::box_builder builder9(m_top_bar.m_texture_manager.get_size("igm_white_cross"));
            builder9.to_center(*m_cross_circle_box);
            m_cross_box.reset(new engine::math::box2_t(builder9.build()));
        }

        void in_game_menu::draw(unsigned int time_elapsed, engine::math::box2_t display_box) {
            m_top_bar.draw(time_elapsed, display_box);

            // Draw the menu icon
            m_top_bar.m_texture_manager.draw("igm_icon", *m_menu_icon_box);

            // Draw the menu and overlay on show
            if (m_show) {
                m_top_bar.m_color_manager.draw({0, 0, 0, 180}, *m_overlay_box);

                // Menu (wrapper)
                m_top_bar.m_texture_manager.draw("igm_grey_panel", *m_menu_box);

                // Menu buttons
                m_top_bar.m_texture_manager.draw("igm_green_btn", *m_save_btn_box);
                m_top_bar.m_texture_manager.draw("igm_save", *m_save_btn_text_box);

                m_top_bar.m_texture_manager.draw("igm_yellow_btn", *m_back_btn_box);
                m_top_bar.m_texture_manager.draw("igm_back", *m_back_btn_text_box);

                m_top_bar.m_texture_manager.draw("igm_red_btn", *m_quit_btn_box);
                m_top_bar.m_texture_manager.draw("igm_quit", *m_quit_btn_text_box);

                // Menu (wrapper) cross
                m_top_bar.m_texture_manager.draw("igm_red_circle", *m_cross_circle_box);
                m_top_bar.m_texture_manager.draw("igm_white_cross", *m_cross_box);
            }
        }

        void in_game_menu::call_on_show_change(std::function<void(bool)> callback) {
            m_callbacks.push_back(callback);
        }

        void in_game_menu::on_event(engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT> &event) {
            auto *position = engine::input::input_handler::get_instance()->get_mouse_position();

            if (m_menu_icon_box->contains(*position)) {
                change_show();
            }

            if (m_show) {
                if (m_quit_btn_box->contains(*position)) {
                    m_top_bar.m_menu_controller->show();
                } else if (m_back_btn_box->contains(*position)|| m_cross_circle_box->contains(*position)) {
                    change_show();
                } else if (m_save_btn_box->contains(*position)) {

                }
            }
        }

        void in_game_menu::on_event(engine::events::key_down &event) {
            if (event.get_keycode() == engine::input::keycodes::keycode::ESCAPE) {
                change_show();
            }
        }

        void in_game_menu::change_show() {
            m_show = !m_show;

            // Call callbacks
            for (auto &callback : m_callbacks) {
                callback(m_show);
            }
        }

        void in_game_menu::after() {
            m_top_bar.after();

            // Unload textures
            m_top_bar.m_texture_manager.unload("igm_icon");
            m_top_bar.m_texture_manager.unload("igm_red_btn");
            m_top_bar.m_texture_manager.unload("igm_yellow_btn");
            m_top_bar.m_texture_manager.unload("igm_green_btn");
            m_top_bar.m_texture_manager.unload("igm_grey_panel");
            m_top_bar.m_texture_manager.unload("igm_grey_cicle");
            m_top_bar.m_texture_manager.unload("igm_white_cross");

            // Unload texts
            m_top_bar.m_texture_manager.unload("igm_save");
            m_top_bar.m_texture_manager.unload("igm_quit");
            m_top_bar.m_texture_manager.unload("igm_back");

            // Unsubscribe to events
            auto &eventbus = engine::eventbus::eventbus::get_instance();

            eventbus.unsubscribe(dynamic_cast<engine::eventbus::subscriber<engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT>>*>(this));
            eventbus.unsubscribe(dynamic_cast<engine::eventbus::subscriber<engine::events::key_down>*>(this));

            // Clear callbacks
            m_callbacks.clear();
        }
    }
}
