//
// Created by robbie on 14-11-2016.
//

#include "credits.h"
#include "../../engine/graphics/box_builder.h"

gui::views::credits::credits(domain::drawable::draw_managers_wrapper &draw_managers, engine::window &window,
                             engine::audio::music_manager &music_manager) :
    m_draw_managers(draw_managers), m_music_manager(music_manager), m_window(window),
    m_header_box(nullptr), m_credits_box(nullptr), m_title_box(nullptr), m_moveable_box(nullptr) {

    m_names.push_back("Robbie op de Weegh");
    m_names.push_back("Leendert Mechielsen");
    m_names.push_back("Jermey Jungbeker");
    m_names.push_back("Rob Hendriks");
    m_names.push_back("Mark Arnoldussen");
    m_names.push_back("Bert Alderliesten");
}

void gui::views::credits::before() {
    // Play some music
    m_music_manager.load("sounds/credits_music.mp3", "credits_bg_music");
    m_music_manager.play("credits_bg_music");
    m_music_manager.set_volume(128);

    // Load the title
    m_draw_managers.texture_manager.load_text("CityDefence", {255, 193, 132},
                                                *m_draw_managers.font_manager.get_font("roboto", 50), "c_title");

    // Load the names
    auto *font = m_draw_managers.font_manager.get_font("roboto", 44);
    for (auto &name : m_names) {
        m_draw_managers.texture_manager.load_text(name, {255, 255, 255}, *font, "n_" + name);
    }
}

void gui::views::credits::on_display_change(engine::math::box2_t display_box) {
    // Create the header box
    engine::graphics::box_builder builder1({display_box.width(), 100});
    builder1.as_left_top(display_box.left_top());
    m_header_box.reset(new engine::math::box2_t(builder1.build()));

    // Create the title box
    engine::graphics::box_builder builder2(m_draw_managers.texture_manager.get_size("c_title"));
    builder2.to_center(*m_header_box);
    m_title_box.reset(new engine::math::box2_t(builder2.build()));

    // Create the credits box
    engine::graphics::box_builder builder3({display_box.width(), display_box.height() - m_header_box->height()});
    builder3.start_on_y(m_header_box->max.y);
    m_credits_box.reset(new engine::math::box2_t(builder3.build()));

    // Create the boxes for the names
    std::vector<engine::math::box2_t> move_boxes;

    for (auto &name : m_names) {
        engine::graphics::box_builder builder4(m_draw_managers.texture_manager.get_size("n_" + name));

        if (move_boxes.size() > 0) {
            builder4.as_left_top(move_boxes.back().left_bottom());
        } else {
            builder4.start_on_y(m_credits_box->min.y);
        }

        builder4.center_horizontal(m_credits_box->min.x, m_credits_box->max.x).add_margin({0, 20});

        // Add to the move_boxes
        move_boxes.push_back(builder4.build());
    }

    // Create a box with move boxes
    m_moveable_box.reset(new engine::graphics::moveable_box(*m_credits_box, move_boxes, {0, -0.1}, -1));
}

void gui::views::credits::after() {
    // Unload the music
    m_music_manager.unload("credits_bg_music");

    // Unload the texts
    m_draw_managers.texture_manager.unload("c_title");

    for (auto &name : m_names) {
        m_draw_managers.texture_manager.unload("n_" + name);
    }
}

void gui::views::credits::draw(unsigned int time_elapsed, engine::math::box2_t display_box) {
    // Draw names
    m_moveable_box->move(time_elapsed);

    int i = 0;
    for (auto &box : m_moveable_box->get_boxes()) {
        m_draw_managers.texture_manager.draw("n_" + m_names[i++], {0, 0}, box);
    }

    // Draw header
    m_draw_managers.color_manager.draw({0, 0, 0}, *m_header_box);
    m_draw_managers.texture_manager.draw("c_title", {0, 0}, *m_title_box);
}
