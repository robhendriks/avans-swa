//
// Created by robbie on 9-1-2017.
//

#include "load.h"
#include "../../engine/graphics/box_builder.h"

namespace gui {
    namespace views {

        load::load(top_bar &top_bar1, models::load_model &load_model) :
            m_top_bar(top_bar1), m_load_model(load_model), m_load_controller(nullptr) {

        }

        void load::before() {
            m_top_bar.before();

            // Subscribe on click event
            engine::eventbus::eventbus::get_instance().subscribe(this);
        }

        void load::on_display_change(engine::math::box2_t display_box) {
            m_top_bar.on_display_change(display_box);
            // Create the boxes for the names
            std::vector<engine::math::box2_t> move_boxes;
            int counter = 0;
            for (auto load_games : m_load_model.saved_games) {
                counter ++;
                // Load textures
                m_top_bar.m_texture_manager.load_text("Game"+ std::to_string(counter), {255, 193, 132},
                                                      *m_top_bar.m_font_manager.get_font("roboto", 70), "c_back");

                std::string name = *load_games;
                engine::graphics::box_builder builder4(m_top_bar.m_texture_manager.get_size("c_green_box"));
                m_back_box1.reset(new engine::math::box2_t(builder4.build()));

                builder4.add_margin({580, 150});
                builder4.build();


                engine::graphics::box_builder builder5(m_top_bar.m_texture_manager.get_size("c_back"));
                builder5.as_left_top(m_back_box1->left_top()).add_margin({580, 150});
                m_back_text_box.reset(new engine::math::box2_t(builder5.build()));

            }
        }

        void load::draw(unsigned int time_elapsed, engine::math::box2_t display_box) {
            m_top_bar.draw(time_elapsed, display_box);
            //loop list last load games
            //m_load_model.get levels

            // Draw the back button
            // m_top_bar.m_texture_manager.draw("c_green_box", *m_back_box);


            for (auto load_games : m_load_model.saved_games) {

                // Draw the back button
                m_top_bar.m_texture_manager.draw("c_green_box", *m_back_box1);
                m_top_bar.m_texture_manager.draw("c_back", *m_back_text_box);

            }


        }

        void load::after() {
            m_top_bar.after();

            // Unsubscribe on click event
            engine::eventbus::eventbus::get_instance().unsubscribe(this);
        }


        void load::on_event(engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT> &event) {
            // Just for now
            engine::math::vec2_t *position = engine::input::input_handler::get_instance()->get_mouse_position();
            if (m_load_model.saved_games.size() > 0) {
                if (m_back_text_box->contains(*position)) {
                    m_load_controller->load(*m_load_model.saved_games.front());
                }
            }
        }

        void load::set_load_controller(controllers::load_controller &load_controller) {
            m_load_controller = &load_controller;
        }
    }
}
