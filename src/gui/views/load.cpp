//
// Created by robbie on 9-1-2017.
//

#include "load.h"
#include "../../engine/graphics/box_builder.h"

namespace gui {
    namespace views {

        load::load(top_bar &top_bar1, models::load_model &load_model) :
            m_top_bar(top_bar1), m_load_model(load_model), m_load_controller(nullptr), m_amount(5) {

        }

        void load::before() {
            m_top_bar.before();

            // Subscribe on click event
            engine::eventbus::eventbus::get_instance().subscribe(this);

            // Load textures
            m_top_bar.m_texture_manager.load_from_svg("images/ui-pack.svg", {{1261, 124}, {1451, 169}}, 2, "l_green_box");
            m_top_bar.m_texture_manager.load("images/load_game.png", "l_load_game");

            // Load the texts
            TTF_Font &font = *m_top_bar.m_font_manager.get_font("roboto", 15);
            for (int i = 0; i < m_amount; i++) {
                int index = m_load_model.saved_games.size() - 1 - i;
                if (index >= 0 && index < m_load_model.saved_games.size()) {
                    std::string filestring = *m_load_model.saved_games[index];
                    std::string date_time_string = filestring.substr (21, 14);
                    std::string formatted = date_time_string.substr(0, 4) + "-" + date_time_string.substr(4, 2) + "-"
                        + date_time_string.substr(6, 2) + " " + date_time_string.substr(8, 2) + ":" +
                        date_time_string.substr(10, 2) + ":" + date_time_string.substr(12, 2);
                    m_top_bar.m_texture_manager.load_text(formatted, {0, 0, 0}, font, "l_" + std::to_string(index));
                }
            }

            m_top_bar.m_texture_manager.load_text("Back to menu", {255, 255, 255},
                                                  *m_top_bar.m_font_manager.get_font("roboto", 25), "l_back_text");
        }

        void load::on_display_change(engine::math::box2_t display_box) {
            m_boxes.clear();
            m_text_boxes.clear();

            m_top_bar.on_display_change(display_box);

            // Create the boxes for the load games
            engine::graphics::box_builder builder1(m_top_bar.m_texture_manager.get_size("l_load_game"));
            builder1.center_vertical(display_box.min.y, display_box.max.y).add_margin({0, -100});
            float x_margin = 50;
            for (int i = 0; i < m_amount; i++) {
                int index = m_load_model.saved_games.size() - 1 - i;
                if (index >= 0 && index < m_load_model.saved_games.size()) {
                    builder1.add_margin({x_margin, 0});
                    auto box = builder1.build();
                    m_boxes.push_back(std::unique_ptr<engine::math::box2_t>(new engine::math::box2_t(box)));

                    engine::graphics::box_builder text_builder(m_top_bar.m_texture_manager.get_size("l_" + std::to_string(index)));
                    text_builder.as_left_bottom(box.left_bottom())
                        .center_horizontal(box.min.x, box.max.x);
                    m_text_boxes.push_back(std::unique_ptr<engine::math::box2_t>(new engine::math::box2_t(text_builder.build())));

                    builder1.add_margin({box.width(), 0});
                }
            }

            // Create the back box
            engine::graphics::box_builder builder2(m_top_bar.m_texture_manager.get_size("l_green_box"));
            builder2.as_left_bottom(display_box.left_bottom()).add_margin({150, -150});
            m_back_box.reset(new engine::math::box2_t(builder2.build()));

            engine::graphics::box_builder builder3(m_top_bar.m_texture_manager.get_size("l_back_text"));
            builder3.to_center(*m_back_box);
            m_back_text_box.reset(new engine::math::box2_t(builder3.build()));
        }

        void load::draw(unsigned int time_elapsed, engine::math::box2_t display_box) {
            m_top_bar.draw(time_elapsed, display_box);

            int box_counter = 0;
            for (int i = 0; i < m_amount; i++) {
                int index = m_load_model.saved_games.size() - 1 - i;
                if (index >= 0 && index < m_load_model.saved_games.size()) {
                    m_top_bar.m_texture_manager.draw("l_load_game", *m_boxes[box_counter]);
                    m_top_bar.m_texture_manager.draw("l_" + std::to_string(i), *m_text_boxes[box_counter]);
                }
                box_counter++;
            }

            m_top_bar.m_texture_manager.draw("l_green_box", *m_back_box);
            m_top_bar.m_texture_manager.draw("l_back_text", *m_back_text_box);
        }

        void load::after() {
            m_top_bar.after();

            // Unsubscribe on click event
            engine::eventbus::eventbus::get_instance().unsubscribe(this);

            // Unload texts
            for (int i = 0; i < m_amount; i++) {
                int index = m_load_model.saved_games.size() - 1 - i;
                if (index >= 0 && index < m_load_model.saved_games.size()) {
                    m_top_bar.m_texture_manager.unload("l_" + std::to_string(i));
                }
            }

            m_top_bar.m_texture_manager.unload("l_back_text");

            // Unload textures
            m_top_bar.m_texture_manager.unload("l_green_box");
            m_top_bar.m_texture_manager.unload("l_load_game");
        }

        void load::on_event(engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT> &event) {
            // Just for now
            engine::math::vec2_t *position = engine::input::input_handler::get_instance()->get_mouse_position();

            int box_counter = 0;
            for (int i = 0; i < m_amount; i++) {
                int index = m_load_model.saved_games.size() - 1 - i;
                if (index >= 0 && index < m_load_model.saved_games.size()) {
                    if (m_boxes[box_counter]->contains(*position)) {
                        m_load_controller->load(*m_load_model.saved_games[index]);
                        return;
                    }

                    box_counter++;
                }
            }

            if (m_back_box->contains(*position)) {
                m_top_bar.m_menu_controller->show();
            }
        }

        void load::set_load_controller(controllers::load_controller &load_controller) {
            m_load_controller = &load_controller;
        }
    }
}
