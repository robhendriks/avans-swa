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

            // Load textures
            m_top_bar.m_texture_manager.load("images/menu_icon.png", "igm_icon");
            m_top_bar.m_texture_manager.load_from_svg("images/ui-pack.svg", {{1261, 184}, {1451, 229}}, 1.5, "igm_red_btn");
            m_top_bar.m_texture_manager.load_from_svg("images/ui-pack.svg", {{1261, 124}, {1451, 169}}, 1.5, "igm_green_btn");

            // Subscribe to events
            auto &eventbus = engine::eventbus::eventbus::get_instance();

            eventbus.subscribe(dynamic_cast<engine::eventbus::subscriber<engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT>>*>(this));
            eventbus.subscribe(dynamic_cast<engine::eventbus::subscriber<engine::events::key_down>*>(this));
        }

        void in_game_menu::on_display_change(engine::math::box2_t display_box) {
            m_top_bar.on_display_change(display_box);

            // Create the menu icon box
            engine::graphics::box_builder builder1(m_top_bar.m_texture_manager.get_size("igm_icon"));
            builder1.as_left_top(m_top_bar.m_bar_box->left_top());
            m_menu_icon_box.reset(new engine::math::box2_t(builder1.build()));

            // Create the overlay box
            engine::graphics::box_builder builder2(display_box.size() - engine::math::vec2_t{0, m_top_bar.m_bar_box->height()});
            builder2.as_left_top(m_top_bar.m_bar_box->left_bottom());
            m_overlay_box.reset(new engine::math::box2_t(builder2.build()));

            // Create the menu box
        }

        void in_game_menu::draw(unsigned int time_elapsed, engine::math::box2_t display_box) {
            m_top_bar.draw(time_elapsed, display_box);

            // Draw the menu icon
            m_top_bar.m_texture_manager.draw("igm_icon", *m_menu_icon_box);

            // Draw the menu and overlay on show
            if (m_show) {
                m_top_bar.m_color_manager.draw({0, 0, 0, 180}, *m_overlay_box);
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
            m_top_bar.m_texture_manager.unload("igm_green_btn");

            // Unsubscribe to events
            auto &eventbus = engine::eventbus::eventbus::get_instance();

            eventbus.unsubscribe(dynamic_cast<engine::eventbus::subscriber<engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT>>*>(this));
            eventbus.unsubscribe(dynamic_cast<engine::eventbus::subscriber<engine::events::key_down>*>(this));
        }
    }
}
