//
// Created by robbie on 14-11-2016.
//

#include "credits.h"
#include "../../engine/graphics/box_builder.h"

gui::views::credits::credits(top_bar &top_bar1, engine::audio::music_manager &music_manager) :
    m_top_bar(top_bar1), m_music_manager(music_manager) {

    m_names.push_back("Robbie op de Weegh");
    m_names.push_back("Leendert Mechielsen");
    m_names.push_back("Jermey Jungbeker");
    m_names.push_back("Rob Hendriks");
    m_names.push_back("Mark Arnoldussen");
    m_names.push_back("Bert Alderliesten");

    m_special_thanks.push_back("With special thanks to:");
    m_special_thanks.push_back("Reinout Versteeg");
    m_special_thanks.push_back("Bart Gelens");
}

void gui::views::credits::before() {
    m_top_bar.before();

    // Play some music
    m_music_manager.load("sounds/credits_music.mp3", "credits_bg_music");
    m_music_manager.play("credits_bg_music");
    m_music_manager.set_volume(128);

    // Load textures
    m_top_bar.m_texture_manager.load_from_svg("images/ui-pack.svg", {{1261, 124}, {1451, 169}}, 2, "c_green_box");
    m_top_bar.m_texture_manager.load_from_svg("images/ui-pack.svg", {{1007, 630}, {1046, 661}}, 0.8, "red_slider_left");

    // Load texts
    m_top_bar.m_texture_manager.load_text("CityDefence", {255, 193, 132},
                                                *m_top_bar.m_font_manager.get_font("roboto", 50), "c_title");

    m_top_bar.m_texture_manager.load_text("Back", {255, 255, 255},
                                          *m_top_bar.m_font_manager.get_font("roboto", 25), "c_back");

    // Load the names
    auto *font = m_top_bar.m_font_manager.get_font("roboto", 44);
    for (auto &name : m_names) {
        m_top_bar.m_texture_manager.load_text(name, {255, 255, 255}, *font, "n_" + name);
    }

    // Load special thanks
    for (auto &special : m_special_thanks) {
        m_top_bar.m_texture_manager.load_text(special, {0, 0, 0}, *font, "n_" + special);
    }

    // Subscribe to events
    auto &eventbus = engine::eventbus::eventbus::get_instance();

    eventbus.subscribe(dynamic_cast<engine::eventbus::subscriber<engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT>>*> (this));
    eventbus.subscribe(dynamic_cast<engine::eventbus::subscriber<engine::events::key_down>*> (this));
}

void gui::views::credits::on_display_change(engine::math::box2_t display_box) {
    m_top_bar.on_display_change(display_box);

    // Create the header box
    engine::graphics::box_builder builder1({display_box.width(), 100});
    builder1.as_left_top(m_top_bar.m_bar_box->left_bottom());
    m_header_box.reset(new engine::math::box2_t(builder1.build()));

    // Create the title box
    engine::graphics::box_builder builder2(m_top_bar.m_texture_manager.get_size("c_title"));
    builder2.to_center(*m_header_box);
    m_title_box.reset(new engine::math::box2_t(builder2.build()));

    // Create the credits box
    engine::graphics::box_builder builder3({display_box.width(), display_box.height() - m_header_box->height()});
    builder3.start_on_y(m_header_box->max.y);
    m_credits_box.reset(new engine::math::box2_t(builder3.build()));

    // Create the boxes for the names
    std::vector<engine::math::box2_t> move_boxes;

    for (auto &name : m_names) {
        engine::graphics::box_builder builder4(m_top_bar.m_texture_manager.get_size("n_" + name));

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

    // Create the back box
    engine::graphics::box_builder builder5(m_top_bar.m_texture_manager.get_size("c_green_box"));
    builder5.center_vertical(m_header_box->min.y, m_header_box->max.y).add_margin({10, 0});
    m_back_box.reset(new engine::math::box2_t(builder5.build()));

    // Create back text box
    engine::graphics::box_builder builder6(m_top_bar.m_texture_manager.get_size("c_back"));
    builder6.as_left_top(m_back_box->left_top()).add_margin({20, 10});
    m_back_text_box.reset(new engine::math::box2_t(builder6.build()));

    // Create the slider move boxes
    auto slider_size = m_top_bar.m_texture_manager.get_size("red_slider_left");

    engine::graphics::box_builder builder7({m_back_box->width() - 6, slider_size.y});
    builder7.as_left_bottom(m_back_box->left_bottom()).add_margin({4, -10});
    m_back_slider_box.reset(new engine::math::box2_t(builder7.build()));

    engine::graphics::box_builder builder8(slider_size);
    builder8.as_right_top(m_back_slider_box->right_top());

    std::vector<engine::math::box2_t> slider_move_boxes;
    for (size_t i = 0; i < 3; i++) {
        auto box = builder8.build();
        slider_move_boxes.push_back(box);
        builder8.add_margin({-(slider_size.x * 2), 0});
    }

    // Reverse the order for a correct animation
    std::reverse(slider_move_boxes.begin(),slider_move_boxes.end());

    m_moveable_slider_box.reset(new engine::graphics::moveable_box(*m_back_slider_box, slider_move_boxes, {-0.3, 0}, -1));

    // Create the special thanks move boxes
    auto special_text_height = m_top_bar.m_texture_manager.get_size("n_" + m_special_thanks[0]).y;
    engine::graphics::box_builder builder9({display_box.width(), special_text_height});
    builder9.center_vertical(move_boxes.back().max.y, display_box.max.y);
    auto special_space_box = builder9.build();

    std::vector<engine::math::box2_t> special_move_boxes;

    for (auto &special : m_special_thanks) {
        engine::graphics::box_builder builder10(m_top_bar.m_texture_manager.get_size("n_" + special));
        if (special_move_boxes.size() > 0) {
            builder10.as_left_top(special_move_boxes.back().right_top());
        } else {
            builder10.to_center(special_space_box);
        }

        builder10.add_margin({static_cast<float>(display_box.width() / 1.3), 0});

        special_move_boxes.push_back(builder10.build());
    }

    m_moveable_special_box.reset(new engine::graphics::moveable_box(special_space_box, special_move_boxes, {-0.6, 0}, -1));
    m_at_slow_speed = false;
}

void gui::views::credits::draw(unsigned int time_elapsed, engine::math::box2_t display_box) {
    m_top_bar.draw(time_elapsed, display_box);

    // Draw names
    m_moveable_box->move(time_elapsed);

    int i = 0;
    for (auto &box : m_moveable_box->get_boxes()) {
        m_top_bar.m_texture_manager.draw("n_" + m_names[i++], box);
    }

    // Draw the special thanks to
    m_moveable_special_box->move(time_elapsed);
    i = 0;
    bool slowed_down = false;
    for (auto &box : m_moveable_special_box->get_boxes()) {
        m_top_bar.m_texture_manager.draw("n_" + m_special_thanks[i++], box);
        if (box.contains({display_box.center().x, box.center().y})) {
            if (!m_at_slow_speed) {
                m_moveable_special_box->change_speed({-0.1, 0});
                m_at_slow_speed = true;
            }

            slowed_down = true;
        }
    }

    if (!slowed_down && m_at_slow_speed) {
        // Back to normal speed
        m_moveable_special_box->change_speed({-0.6, 0});
        m_at_slow_speed = false;
    }

    // Draw header
    m_top_bar.m_color_manager.draw({0, 0, 0}, *m_header_box);
    m_top_bar.m_texture_manager.draw("c_title", *m_title_box);

    // Draw the back button
    m_top_bar.m_texture_manager.draw("c_green_box", *m_back_box);
    m_top_bar.m_texture_manager.draw("c_back", *m_back_text_box);

    m_moveable_slider_box->move(time_elapsed);
    for (auto &box : m_moveable_slider_box->get_boxes()) {
        if (m_back_slider_box->contains(box)) {
            m_top_bar.m_texture_manager.draw("red_slider_left", box);
        } else {
            if (m_back_slider_box->contains(box.min)) {
                auto show_box = engine::math::box2_t(box.min, m_back_slider_box->max);
                m_top_bar.m_texture_manager.draw("red_slider_left", {0, 0}, show_box);
            } else if (m_back_slider_box->contains(box.max)) {
                auto show_box = engine::math::box2_t(m_back_slider_box->min, box.max);
                m_top_bar.m_texture_manager.draw("red_slider_left", {show_box.min.x - box.min.x, 0}, show_box);
            }
        }
    }
}

void gui::views::credits::on_event(engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT> &event) {
    engine::math::vec2_t *position = engine::input::input_handler::get_instance()->get_mouse_position();

    if (m_back_box->contains(*position)) {
        m_top_bar.m_menu_controller->show();
    }
}

void gui::views::credits::on_event(engine::events::key_down &event) {
    if (event.get_keycode() == engine::input::keycodes::keycode::ESCAPE) {
        m_top_bar.m_menu_controller->show();
    }
}

void gui::views::credits::after() {
    m_top_bar.after();

    // Unload the music
    m_music_manager.unload("credits_bg_music");

    // Unload textures
    m_top_bar.m_texture_manager.unload("c_green_box");
    m_top_bar.m_texture_manager.unload("red_slider_left");

    // Unload texts
    m_top_bar.m_texture_manager.unload("c_title");
    m_top_bar.m_texture_manager.unload("c_back");

    for (auto &name : m_names) {
        m_top_bar.m_texture_manager.unload("n_" + name);
    }

    for (auto &special : m_special_thanks) {
        m_top_bar.m_texture_manager.unload("n_" + special);
    }

    // Unsubscribe to events
    auto &eventbus = engine::eventbus::eventbus::get_instance();

    eventbus.unsubscribe(dynamic_cast<engine::eventbus::subscriber<engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT>>*> (this));
    eventbus.unsubscribe(dynamic_cast<engine::eventbus::subscriber<engine::events::key_down>*> (this));
}
