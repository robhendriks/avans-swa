//
// Created by Bert on 21-12-2016.
//

#include "mayor_view.h"
#include "../../engine/graphics/box_builder.h"

gui::views::mayor_view::mayor_view(domain::drawable::draw_managers_wrapper &draw_managers) : m_draw_managers(draw_managers){}

void gui::views::mayor_view::before() {
    m_show = true;

    // Load textures
    m_draw_managers.texture_manager.load("mayor_bart", "img_mayor_bart");

    // Load texts
    m_draw_managers.texture_manager.load_text("Burgemeester", {255, 255, 255},
                                              *m_draw_managers.font_manager.get_font("roboto", 25), "mayor_text");
}

void gui::views::mayor_view::on_display_change(engine::math::box2_t display_box) {
    // Create mayor_view box on the right
    engine::graphics::box_builder builder1(m_draw_managers.texture_manager.get_size("img_mayor_bart"));
    m_mayor_box.reset(new engine::math::box2_t(builder1.build()));
}

void gui::views::mayor_view::draw(unsigned int time_elapsed, engine::math::box2_t display_box) {
    if (m_show){
        m_draw_managers.texture_manager.draw("img_mayor_bart", *m_mayor_box);

        engine::graphics::box_builder builder1(m_draw_managers.texture_manager.get_size("mayor_text"));
        builder1.to_center(*m_mayor_box);
        m_draw_managers.texture_manager.draw("mayor_text", builder1.build());
    }

}

void gui::views::mayor_view::after() {
    m_draw_managers.texture_manager.unload("img_mayor_bart");
    m_draw_managers.texture_manager.unload("mayor_text");
}

void gui::views::mayor_view::change_show() {
    m_show = !m_show;
}
