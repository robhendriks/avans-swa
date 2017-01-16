//
// Created by Bert on 21-12-2016.
//

#include "mayor_view.h"
#include "../../engine/graphics/box_builder.h"

gui::views::mayor_view::mayor_view(domain::drawable::draw_managers_wrapper &draw_managers) : m_draw_managers(
        draw_managers) {}

void gui::views::mayor_view::before() {
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
    //current response renewal
    m_current_display_time = time_elapsed - m_last_transition_time;
    if (m_current_display_time > m_max_display_time) {
        m_current_response = m_mayor->get_fifo_milestone_response();
        if(m_current_response == ""){
            m_current_response = "I have nothing to say";
        }
        m_last_transition_time = time_elapsed;
    }

    m_draw_managers.texture_manager.unload("mayor_text");
    m_draw_managers.texture_manager.load_text(m_current_response, {255, 255, 255},
                                              *m_draw_managers.font_manager.get_font("roboto", 14), "mayor_text", 150);

    engine::math::vec2_t margin = {display_box.max.x - m_mayor_box->size().x - 20, display_box.max.y - m_mayor_box->size().y - 100};
    auto mayor_img_size = m_draw_managers.texture_manager.get_size("img_mayor_bart");
    auto mayor_text_size = m_draw_managers.texture_manager.get_size("mayor_text");
    engine::graphics::box_builder builder(mayor_img_size);
    engine::graphics::box_builder builder1(mayor_text_size);
    builder.as_left_top(m_mayor_box->left_top()).center_vertical(m_mayor_box->min.y, m_mayor_box->max.y)
            .add_margin(margin);
    builder1.as_left_top(m_mayor_box->left_top()).center_vertical(m_mayor_box->min.y, m_mayor_box->max.y)
            .add_margin({margin.x, margin.y + 200});

    m_draw_managers.texture_manager.draw("img_mayor_bart", builder.build());
    m_draw_managers.texture_manager.draw("mayor_text", builder1.build());
}

void gui::views::mayor_view::after() {
    m_draw_managers.texture_manager.unload("img_mayor_bart");
    m_draw_managers.texture_manager.unload("mayor_text");
}

void gui::views::mayor_view::set_mayor(domain::mayor* _mayor) {
    m_mayor = _mayor;
}

void gui::views::mayor_view::set_current_response(const std::string &response) {
    m_current_response = response;
}
