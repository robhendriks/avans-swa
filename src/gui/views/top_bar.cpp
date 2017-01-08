//
// Created by robbie on 1-12-2016.
//

#include "top_bar.h"
#include "../../engine/graphics/box_builder.h"

namespace gui {
    namespace views {

        top_bar::top_bar(domain::drawable::draw_managers_wrapper &draw_managers, engine::engine &engine) :
            m_draw_managers(draw_managers), m_engine(engine),
            m_texture_manager(draw_managers.texture_manager), m_color_manager(draw_managers.color_manager),
            m_font_manager(draw_managers.font_manager), m_menu_controller(nullptr), m_previous_draw_time(0),
            m_fps(0), m_fps_show(false) {

        }

        void top_bar::set_controller(controllers::menu_controller &menu_controller) {
            m_menu_controller = &menu_controller;
        }

        void top_bar::before() {
            m_texture_manager.load("images/close.png", "t_p_close");

            // Subscribe to eventbus
            auto &eventbus = engine::eventbus::eventbus::get_instance();
            eventbus.subscribe(dynamic_cast<engine::eventbus::subscriber<engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT>>*> (this));
            eventbus.subscribe(dynamic_cast<engine::eventbus::subscriber<engine::events::key_down>*> (this));
        }

        void top_bar::on_display_change(engine::math::box2_t display_box) {
            // Create the bar box
            engine::graphics::box_builder builder1({display_box.width(), 32});
            m_bar_box.reset(new engine::math::box2_t(builder1.build()));

            // Create the close box
            engine::graphics::box_builder builder2(m_texture_manager.get_size("t_p_close"));
            builder2.as_right_top(m_bar_box->right_top());
            m_close_box.reset(new engine::math::box2_t(builder2.build()));
        }

        void top_bar::draw(unsigned int time_elapsed, engine::math::box2_t display_box) {
            m_color_manager.draw({64, 64, 64, 128}, *m_bar_box);

            m_texture_manager.draw("t_p_close", {0, 0}, *m_close_box);

            if (m_fps_show) {
                // Refresh every half second
                if (m_engine.get_real_time_elapsed() - m_previous_draw_time >= 500 || m_previous_draw_time == 0) {
                    m_previous_draw_time = m_engine.get_real_time_elapsed();
                    m_fps = m_engine.get_fps();
                }

                // Show the fps
                std::string fps_text = std::to_string(m_fps) + " FPS";
                m_texture_manager.load_text(fps_text, {255, 255, 255}, *m_font_manager.get_font("roboto", 18), "t_p_fps");
                engine::graphics::box_builder builder(m_texture_manager.get_size("t_p_fps"));
                builder.as_right_top(m_close_box->left_top()).add_margin({-10, 0})
                    .center_vertical(m_close_box->min.y, m_close_box->max.y);
                m_texture_manager.draw("t_p_fps", builder.build());
            }
        }

        void top_bar::after() {
            m_texture_manager.unload("t_p_close");

            // Unsubscribe eventbus
            auto &eventbus = engine::eventbus::eventbus::get_instance();
            eventbus.unsubscribe(dynamic_cast<engine::eventbus::subscriber<engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT>>*> (this));
            eventbus.unsubscribe(dynamic_cast<engine::eventbus::subscriber<engine::events::key_down>*> (this));
        }

        void top_bar::on_event(engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT> &event) {
            auto *position = engine::input::input_handler::get_instance()->get_mouse_position();
            if (m_close_box->contains(*position)) {
                m_menu_controller->quit();
            }
        }

        void top_bar::on_event(engine::events::key_down &event) {
            if (event.get_keycode() == engine::input::keycodes::keycode::F1) {
                m_fps_show = !m_fps_show;
                m_previous_draw_time = 0;
            }
        }
    }
}
