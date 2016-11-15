//
// Created by robbie on 14-11-2016.
//

#include "credits.h"

gui::views::credits::credits(engine::graphics::texture_manager &texture_manager,
                             engine::graphics::font_manager &font_manager,
                             engine::graphics::color_manager &color_manager, engine::window &window,
                             engine::engine &engine1, engine::audio::music_manager &music_manager) :
    m_texture_manager(texture_manager), m_font_manager(font_manager), m_color_manager(color_manager),
    m_music_manager(music_manager), m_window(window), m_engine(engine1),
    m_header_box({{0, 0}, {m_window.get_display_box().max.x, 100}}),
    m_credits_box({{0, m_header_box.max.y + 1}, {m_header_box.max.x, m_window.get_display_box().max.y}}),
    m_title_box(nullptr), m_moveable_box(nullptr) {

    m_names.push_back("Robbie op de Weegh");
    m_names.push_back("Leendert Mechielsen");
    m_names.push_back("Jermey Jungbeker");
    m_names.push_back("Rob Hendriks");
    m_names.push_back("Mark Arnoldussen");
    m_names.push_back("Bert Alderliesten");
}

void gui::views::credits::before() {
    // Play some music
    m_music_manager.load("sounds/uaoi.mp3", "credits_bg_music");
    m_music_manager.play("credits_bg_music");

    // Load the title
    m_texture_manager.load_text("CityDefence", {255, 193, 132}, *m_font_manager.get_font("test", 50), "c_title");
    int title_width = m_texture_manager.get_width("c_title");
    int title_height = m_texture_manager.get_height("c_title");

    // Create the title box
    m_title_box = new engine::math::box2_t({{0, 0}, {(float) title_width, (float) title_height}});
    m_title_box->to_center(m_header_box);

    // Load the names
    auto *font = m_font_manager.get_font("test", 24);
    for (auto &name : m_names) {
        m_texture_manager.load_text(name, {255, 255, 255}, *font, "n_" + name);
    }

    // Create the boxes for the names
    std::vector<engine::math::box2_t> move_boxes;

    float padding = 20;
    engine::math::vec2_t name_pos = {0, padding};

    for (auto &name : m_names) {
        int text_width = m_texture_manager.get_width("n_" + name);
        int text_height = m_texture_manager.get_height("n_" + name);
        engine::math::box2_t text_box = {{0, 0}, {(float) text_width, (float) text_height}};

        // Center
        text_box.to_center(m_credits_box);
        text_box.to_top(m_credits_box);
        text_box.add(name_pos);

        // Add to the move_boxes
        move_boxes.push_back(text_box);

        // Increase the height for the next box
        name_pos.y += text_height + padding;
    }

    // Create a box with move boxes
    m_moveable_box = new engine::graphics::moveable_box(m_credits_box, move_boxes, {0, -0.1}, -1);
}

void gui::views::credits::after() {
    // Unload the music
    m_music_manager.unload("credits_bg_music");

    // Unload the texts
    m_texture_manager.unload("c_title");

    for (auto &name : m_names) {
        m_texture_manager.unload("n_" + name);
    }

    delete m_title_box;
}

void gui::views::credits::draw(float interpolation) {
    // Draw names
    m_moveable_box->move(m_engine.get_time_elapsed());

    int i = 0;
    for (auto &box : m_moveable_box->get_boxes()) {
        m_texture_manager.draw("n_" + m_names[i++], {0, 0}, box);
    }

    // Draw header
    m_color_manager.draw({0, 0, 0}, m_header_box);
    m_texture_manager.draw("c_title", {0, 0}, *m_title_box);
}