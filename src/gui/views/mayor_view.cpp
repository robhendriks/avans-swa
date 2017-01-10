//
// Created by Bert on 21-12-2016.
//

#include "mayor_view.h"
#include "../../engine/graphics/box_builder.h"

gui::views::mayor_view::mayor_view(domain::drawable::draw_managers_wrapper &draw_managers) : m_draw_managers(
        draw_managers) {}

void gui::views::mayor_view::before() {
    m_show = true;

    // Load textures
    m_draw_managers.texture_manager.load("images/mayor_bart.png", "img_mayor_bart");

    auto mayor_name = m_mayor != nullptr ? m_mayor->get_name() : "Burgemeester";
    // Load texts
    m_draw_managers.texture_manager.load_text(mayor_name, {255, 255, 255},
                                              *m_draw_managers.font_manager.get_font("roboto", 25), "mayor_text");

    m_draw_managers.texture_manager.load_text(m_current_response, {255, 255, 255},
                                              *m_draw_managers.font_manager.get_font("roboto", 14), "mayor_text", 150);
}

void gui::views::mayor_view::on_display_change(engine::math::box2_t display_box) {
    // Create mayor_view box on the right
    engine::graphics::box_builder builder1(m_draw_managers.texture_manager.get_size("img_mayor_bart"));
    m_mayor_box.reset(new engine::math::box2_t(builder1.build()));
}

void gui::views::mayor_view::draw(unsigned int time_elapsed, engine::math::box2_t display_box) {
    auto mayor_img_size = m_draw_managers.texture_manager.get_size("img_mayor_bart");
    auto mayor_text_size = m_draw_managers.texture_manager.get_size("mayor_text");
    engine::graphics::box_builder builder(mayor_img_size);
    engine::graphics::box_builder builder1(mayor_text_size);

    // set box to hidden place
    set_boxes(display_box);

//    builder.add_margin({display_box.max.x, display_box.max.y - mayor_text_size.y - mayor_img_size.y});
//    builder1.add_margin({display_box.max.x, display_box.max.y - mayor_text_size.y - 300});

    if (m_state == visible) {
        m_current_display_time = time_elapsed - m_last_transition_time;

        if (m_current_display_time > m_max_display_time) {
            builder.add_margin({-mayor_text_size.x - mayor_img_size.x, 0});
            builder1.add_margin({-mayor_text_size.x - 100, 0});

            m_previous_state = m_state;
            m_state = animating;
            m_last_transition_time = time_elapsed;
        }
    } else if (m_state == animating) {
        // count movement percentage
        auto size_x = mayor_img_size.x + mayor_text_size.x;

        // timer for the position of the box
        auto current_time_moved = time_elapsed - m_time_moved;
        auto speed = static_cast<double>(size_x) / static_cast<double>(m_max_animation_time);

        // % of total time
        double percentage = static_cast<double>(current_time_moved) / speed * 100;

        // if completely moved set state
        if (percentage >= 100) {
            if (m_previous_state == hidden) {
                m_state = visible;
            } else {
                m_state = hidden;
            }
        } else {
            if (m_previous_state == hidden) {
//                engine::math::vec2_t vec_min = {static_cast<float>(m_init_box->min.x - (speed * percentage)),
//                                                static_cast<float>(0)};
//                engine::math::vec2_t vec_max = {static_cast<float>(m_init_box->max.x - (speed * percentage)),
//                                                static_cast<float>(0)};
//
//                // Pointer to new position of the box, draw on screen
//                //std::unique_ptr<engine::math::box2_t> new_box = new engine::math::box2_t{vec_min, vec_max};
//                // draw
            } else {
//                engine::math::vec2_t vec_min = {static_cast<float>(m_init_box->min.x + (speed * percentage)),
//                                                static_cast<float>(0)};
//                engine::math::vec2_t vec_max = {static_cast<float>(m_init_box->max.x + (speed * percentage)),
//                                                static_cast<float>(0)};
//                // Pointer to new position of the box, draw on screen
//                //std::unique_ptr<engine::math::box2_t> new_box = new engine::math::box2_t{vec_min, vec_max};
//                // draw
            }
        }
    } else {
        // go to hidden state
        // todo uitwerken
        m_previous_state = m_state;

        m_state = animating;
        m_last_transition_time = time_elapsed;
    }


    m_draw_managers.texture_manager.draw("img_mayor_bart", builder.build());
    m_draw_managers.texture_manager.draw("mayor_text", builder1.build());
}

void gui::views::mayor_view::after() {
    m_draw_managers.texture_manager.unload("img_mayor_bart");
    m_draw_managers.texture_manager.unload("mayor_text");
}

void gui::views::mayor_view::change_show() {
    m_show = !m_show;
}

void gui::views::mayor_view::set_mayor(domain::mayor* _mayor) {
    m_mayor = _mayor;
}

void gui::views::mayor_view::set_boxes(const engine::math::box2_t display_box) {
    auto mayor_img_size = m_draw_managers.texture_manager.get_size("img_mayor_bart");
    auto mayor_text_size = m_draw_managers.texture_manager.get_size("mayor_text");

    auto vec_min_hidden = engine::math::vec2_t{display_box.max.x,
                                               display_box.max.y - mayor_text_size.y - mayor_img_size.y};
    auto vec_max_hidden = engine::math::vec2_t{display_box.max.x + mayor_text_size.x + mayor_img_size.x,
                                               display_box.max.y - mayor_text_size.y - mayor_img_size.y};

    m_init_box.reset(new engine::math::box2_t(vec_min_hidden, vec_max_hidden));
    m_dest_box.reset(
            new engine::math::box2_t{{m_init_box->min.x - mayor_text_size.x - mayor_img_size.x, m_init_box->min.y},
                                     {display_box.max.x,                                        display_box.max.y -
                                                                                                mayor_text_size.y -
                                                                                                mayor_img_size.y}});
}

void gui::views::mayor_view::set_current_response(const std::string &response) {
    m_current_response = response;
}
