//
// Created by robbie on 1-12-2016.
//

#include "top_bar.h"
#include "../../engine/graphics/box_builder.h"

namespace gui {
    namespace views {

        top_bar::top_bar(domain::drawable::draw_managers_wrapper &draw_managers) : m_draw_managers(draw_managers),
            m_texture_manager(draw_managers.texture_manager), m_color_manager(draw_managers.color_manager),
            m_font_manager(draw_managers.font_manager), m_menu_controller(nullptr) {

        }

        void top_bar::set_controller(std::shared_ptr<controllers::menu_controller> menu_controller) {
            m_menu_controller = menu_controller;
        }

        void top_bar::before() {
            m_texture_manager.load("images/close.png", "t_p_close");

            engine::eventbus::eventbus::get_instance().subscribe(this);
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
        }

        void top_bar::after() {
            m_texture_manager.unload("t_p_close");

            engine::eventbus::eventbus::get_instance().unsubscribe(this);
        }

        void top_bar::on_event(engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT> &event) {
            auto *position = engine::input::input_handler::get_instance()->get_mouse_position();
            if (m_close_box->contains(*position)) {
                m_menu_controller->quit();
            }
        }
    }
}
