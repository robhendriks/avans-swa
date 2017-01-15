//
// Created by te on 19-Nov-16.
//

#include "win_game_over.h"
#include "../../engine/graphics/box_builder.h"
#include "../../utils/string_utils.h"

namespace gui {
    namespace views {

        win_game_over::win_game_over(in_game_menu &in_game_menu1, level_goals &goals_view, models::transition_level_model &model,
            engine::audio::sound_manager &sound_manager) :
                m_in_game_menu(in_game_menu1), m_goals_view(goals_view), m_controller(nullptr), m_model(model),
                m_sound_manager(sound_manager), m_texture_manager(m_in_game_menu.m_help_view.m_top_bar.m_texture_manager),
                m_color_manager(m_in_game_menu.m_help_view.m_top_bar.m_color_manager),
                m_font_manager(m_in_game_menu.m_help_view.m_top_bar.m_font_manager) {

        }

        void win_game_over::before() {
            m_in_game_menu.before();
            m_goals_view.before();

            // Load textures
            m_texture_manager.load("images/background-game.png", "background-game");

            m_texture_manager.load_from_svg("images/ui-pack.svg", {{1261, 124}, {1451, 169}}, 2, "w_green_box");
            m_texture_manager.load_from_svg("images/ui-pack.svg", {{1261, 184}, {1451, 229}}, 1.5, "w_red_box");
            m_texture_manager.load_from_svg("images/ui-pack.svg", {{1080, 630}, {1119, 661}}, 0.8, "red_slider_right");

            // Load texts
            std::string result = m_model.result ? "Victory" : "Defeat";
            std::string last = m_model.next_lvl_exists ? "" : " - last level";
            m_texture_manager.load_text(result + last, {255, 193, 132}, *m_font_manager.get_font("roboto", 50), "w_title");

            m_texture_manager.load_text("Duration", {255, 255, 255}, *m_font_manager.get_font("roboto", 25), "w_time");
            m_texture_manager.load_text(utils::string_utils::ms_to_hms(m_model.duration), {0, 0, 0}, *m_font_manager.get_font("roboto", 25), "w_time_played");
            m_texture_manager.load_text("Continue", {255, 255, 255}, *m_font_manager.get_font("roboto", 25), "w_continue");

            if (!m_model.next_lvl_exists || !m_model.result) {
                m_texture_manager.load_text("Highscores", {255, 255, 255}, *m_font_manager.get_font("roboto", 25), "w_h_title");

                m_texture_manager.load_text("Your score: " + std::to_string(m_model.score->get_score()), {0, 0, 0}, *m_font_manager.get_font("roboto", 30), "w_h_score");

                // Load texts highscores
                int counter = 0;
                auto &font = *m_font_manager.get_font("roboto", 12);
                for (auto &highscore : m_model.highscores) {
                    if (counter > 4) {
                        break;
                    }

                    engine::graphics::color4_t color{0, 0, 0};
                    if (highscore.get_time() == m_model.score->get_time()) {
                        color.g = 255;
                    }

                    std::string counter_string = std::to_string(counter + 1);
                    m_texture_manager.load_text(counter_string + ".", color, font, "wh_n_" + counter_string);

                    char buff[20];
                    time_t time = highscore.get_time();
                    strftime(buff, 20, "%Y-%m-%d %H:%M:%S", std::localtime(&time));
//                    m_texture_manager.load_text(std::to_string(ltm->tm_year) + "-" + std::to_string(ltm->tm_mon) +
//                                                    "-" + std::to_string(ltm->tm_mday) + " " +
//                                                    std::to_string(ltm->tm_hour) + ":" + std::to_string(ltm->tm_min) +
//                                                    ":" + std::to_string(ltm->tm_sec), {0, 0, 0}, font,
//                                                "wh_d_" + counter_string);

                    m_texture_manager.load_text(buff, color, font, "wh_d_" + counter_string);
                    m_texture_manager.load_text(std::to_string(highscore.get_score()), color, font,
                                                "wh_s_" + counter_string);

                    counter++;
                }
            }

            // Load and play sound effect
            if (m_model.result) {
                m_sound_manager.load("sounds/winner.wav", "w_sound");
            } else {
                m_sound_manager.load("sounds/loser.wav", "w_sound");
            }

            m_sound_manager.play("w_sound");

            // Subscribe on click event
            engine::eventbus::eventbus::get_instance().subscribe(this);
        }

        void win_game_over::on_display_change(engine::math::box2_t display_box) {
            m_highscore_boxes.clear();

            m_in_game_menu.on_display_change(display_box);
            m_goals_view.on_display_change(display_box);

            // Create title box
            engine::graphics::box_builder builder1(m_texture_manager.get_size("w_title"));
            builder1.as_left_top(m_in_game_menu.m_help_view.m_top_bar.m_bar_box->left_bottom()).add_margin({0, 40})
                .center_horizontal(m_in_game_menu.m_help_view.m_top_bar.m_bar_box->min.x, m_in_game_menu.m_help_view.m_top_bar.m_bar_box->max.x);
            m_title_box.reset(new engine::math::box2_t(builder1.build()));

            // Create the highscore boxes
            int counter = 0;
            float largest_width_1 = -1;
            float largest_width_2 = -1;
            float largest_width_3 = -1;
            float height = 0;
            for (auto &highscore : m_model.highscores) {
                if (counter > 4) {
                    break;
                }

                std::string counter_string = std::to_string(counter + 1);
                engine::graphics::box_builder h_builder1(m_texture_manager.get_size("wh_n_" + counter_string));
                engine::graphics::box_builder h_builder2(m_texture_manager.get_size("wh_d_" + counter_string));
                engine::graphics::box_builder h_builder3(m_texture_manager.get_size("wh_s_" + counter_string));

                m_highscore_boxes.push_back(std::make_tuple(
                    std::unique_ptr<engine::math::box2_t>(new engine::math::box2_t(h_builder1.build())),
                    std::unique_ptr<engine::math::box2_t>(new engine::math::box2_t(h_builder2.build())),
                    std::unique_ptr<engine::math::box2_t>(new engine::math::box2_t(h_builder3.build()))
                ));

                if (largest_width_1 == -1 || h_builder1.build().width() > largest_width_1) {
                    largest_width_1 = h_builder1.build().width();
                }

                if (largest_width_2 == -1 || h_builder2.build().width() > largest_width_2) {
                    largest_width_2 = h_builder2.build().width();
                }

                if (largest_width_3 == -1 || h_builder3.build().width() > largest_width_3) {
                    largest_width_3 = h_builder3.build().width();
                }

                height += 20;
                counter++;
            }

            engine::graphics::box_builder highscores_wrapper_box_builder({largest_width_1 + largest_width_2 + largest_width_3 + 60, height});
            highscores_wrapper_box_builder.as_left_top(m_title_box->left_bottom())
                .center_horizontal(display_box.min.x, display_box.max.x);
            engine::math::box2_t highscores_wrapper_box = highscores_wrapper_box_builder.build();

            engine::graphics::box_builder score_box_builder(m_texture_manager.get_size("w_h_score"));
            score_box_builder.as_left_top(highscores_wrapper_box.left_top()).add_margin({0, 20})
                .center_horizontal(display_box.min.x, display_box.max.x);
            m_own_score_box.reset(new engine::math::box2_t(score_box_builder.build()));

            engine::graphics::box_builder highscore_title_box_builder(m_texture_manager.get_size("w_h_title"));
            highscore_title_box_builder.as_left_top(m_own_score_box->left_bottom())
                .add_margin({0, 25}).center_horizontal(display_box.min.x, display_box.max.x);
            m_highscores_title_box.reset(new engine::math::box2_t(highscore_title_box_builder.build()));

            highscores_wrapper_box_builder.as_left_top(m_highscores_title_box->left_bottom()).add_margin({0, 5})
                .center_horizontal(display_box.min.x, display_box.max.x);
            highscores_wrapper_box = highscores_wrapper_box_builder.build();

            float h_margin = 0;
            for (auto &h_b : m_highscore_boxes) {
                engine::graphics::box_builder temp_box_1(std::get<0>(h_b)->size());
                temp_box_1.as_left_top(highscores_wrapper_box.left_top()).add_margin({0, h_margin});

                engine::graphics::box_builder temp_box_2(std::get<1>(h_b)->size());
                temp_box_2.as_left_top(highscores_wrapper_box.left_top()).add_margin({largest_width_1 + 30, h_margin});

                engine::graphics::box_builder temp_box_3(std::get<2>(h_b)->size());
                temp_box_3.as_left_top(highscores_wrapper_box.left_top()).add_margin({largest_width_2 + largest_width_1 + 60, h_margin});

                std::get<0>(h_b).reset(new engine::math::box2_t(temp_box_1.build()));
                std::get<1>(h_b).reset(new engine::math::box2_t(temp_box_2.build()));
                std::get<2>(h_b).reset(new engine::math::box2_t(temp_box_3.build()));

                h_margin += 20;
            }

            // Create the continue box
            engine::graphics::box_builder builder2(m_texture_manager.get_size("w_green_box"));
            builder2.as_right_bottom(display_box.right_bottom()).add_margin({-150, -150});
            m_continue_box.reset(new engine::math::box2_t(builder2.build()));

            // Create continue text box
            engine::graphics::box_builder builder3(m_texture_manager.get_size("w_continue"));
            builder3.as_left_top(m_continue_box->left_top()).add_margin({20, 10});
            m_continue_text_box.reset(new engine::math::box2_t(builder3.build()));

            // Create the slider move boxes
            auto slider_size = m_texture_manager.get_size("red_slider_right");

            engine::graphics::box_builder builder5({m_continue_box->width() - 6, slider_size.y});
            builder5.as_left_bottom(m_continue_box->left_bottom()).add_margin({4, -10});

            m_continue_slider_box.reset(new engine::math::box2_t(builder5.build()));

            engine::graphics::box_builder builder4(slider_size);
            builder4.as_left_top(m_continue_slider_box->left_top()).add_margin({-40, 0});

            std::vector<engine::math::box2_t> slider_move_boxes;
            for (size_t i = 0; i < 3; i++) {
                auto box = builder4.build();
                slider_move_boxes.push_back(box);
                builder4.add_margin({slider_size.x * 2, 0});
            }

            m_moveable_slider_box.reset(new engine::graphics::moveable_box(*m_continue_slider_box, slider_move_boxes, {0.3, 0}, -1));

            auto time_header_size = m_texture_manager.get_size("w_red_box");
            auto stats_header_size = m_goals_view.m_stats_header_box->size();

            // Stats wrapper box
            engine::graphics::box_builder builder11(time_header_size + stats_header_size + 50);
            builder11.as_left_top(highscores_wrapper_box.left_bottom())
                .center_horizontal(m_title_box->min.x, m_title_box->max.x)
                .center_vertical(highscores_wrapper_box.max.y, m_continue_box->min.y).add_margin({0, -70});
            auto wrapper_box = builder11.build();

            // Create the time header box
            engine::graphics::box_builder builder7(time_header_size);
            builder7.as_right_top(wrapper_box.right_top());
            m_time_header_box.reset(new engine::math::box2_t(builder7.build()));

            // Create the time header text box
            engine::graphics::box_builder builder8(m_texture_manager.get_size("w_time"));
            builder8.to_center(*m_time_header_box);
            m_time_header_text_box.reset(new engine::math::box2_t(builder8.build()));

            // Create the time box
            engine::graphics::box_builder builder9(m_texture_manager.get_size("g_box"));
            builder9.as_left_top(m_time_header_box->left_bottom()).add_margin({0, 10});
            m_time_box.reset(new engine::math::box2_t(builder9.build()));

            // Create the time text box
            engine::graphics::box_builder builder10(m_texture_manager.get_size("w_time_played"));
            builder10.to_center(*m_time_box);
            m_time_text_box.reset(new engine::math::box2_t(builder10.build()));

            // Reposition the goals box
            engine::graphics::box_builder builder6(stats_header_size);
            builder6.as_left_top(wrapper_box.left_top());
            m_goals_view.m_stats_header_box.reset(new engine::math::box2_t(builder6.build()));
        }

        void win_game_over::draw(unsigned int time_elapsed, engine::math::box2_t display_box) {
            m_texture_manager.draw("background-game", display_box);

            m_goals_view.draw(time_elapsed, display_box);

            m_texture_manager.draw("w_title", *m_title_box);
            m_texture_manager.draw("w_red_box", *m_time_header_box);
            m_texture_manager.draw("w_time", *m_time_header_text_box);
            m_texture_manager.draw("g_box", *m_time_box);
            m_texture_manager.draw("w_time_played", *m_time_text_box);
            m_texture_manager.draw("w_green_box", *m_continue_box);
            m_texture_manager.draw("w_continue", *m_continue_text_box);

            m_moveable_slider_box->move(time_elapsed);
            for (auto &box : m_moveable_slider_box->get_boxes()) {
                if (m_continue_slider_box->contains(box)) {
                    m_texture_manager.draw("red_slider_right", box);
                } else {
                    if (m_continue_slider_box->contains(box.min)) {
                        auto show_box = engine::math::box2_t(box.min, m_continue_slider_box->max);
                        m_texture_manager.draw("red_slider_right", {0, 0}, show_box);
                    } else if (m_continue_slider_box->contains(box.max)) {
                        auto show_box = engine::math::box2_t(m_continue_slider_box->min, box.max);
                        m_texture_manager.draw("red_slider_right", {show_box.min.x - box.min.x, 0}, show_box);
                    }
                }
            }

            if (!m_model.next_lvl_exists || !m_model.result) {
                // Draw the highscores
                m_texture_manager.draw("w_h_title", *m_highscores_title_box);

                // Draw the own score
                m_texture_manager.draw("w_h_score", *m_own_score_box);

                // Draw the top 5
                int counter = 0;
                for (auto &highscore : m_model.highscores) {
                    if (counter > 4) {
                        break;
                    }

                    std::string counter_string = std::to_string(counter + 1);

                    m_texture_manager.draw("wh_n_" + counter_string, *std::get<0>(m_highscore_boxes[counter]));
                    m_texture_manager.draw("wh_d_" + counter_string, *std::get<1>(m_highscore_boxes[counter]));
                    m_texture_manager.draw("wh_s_" + counter_string, *std::get<2>(m_highscore_boxes[counter]));

                    counter++;
                }
            }

            // Draw at last because of the overlay
            m_in_game_menu.draw(time_elapsed, display_box);
        }

        void win_game_over::on_event(engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT> &event) {
            engine::math::vec2_t *position = engine::input::input_handler::get_instance()->get_mouse_position();

            if (m_continue_box->contains(*position)) {
                m_controller->next_lvl();
            }
        }

        void win_game_over::set_controller(gui::controllers::main_map_controller &controller) {
            m_controller = &controller;
            m_in_game_menu.set_controller(controller);
        }

        void win_game_over::after() {
            m_in_game_menu.after();
            m_goals_view.after();

            // Unload textures
            m_texture_manager.unload("w_green_box");
            m_texture_manager.unload("w_red_box");
            m_texture_manager.unload("red_slider_right");
            m_texture_manager.unload("background-game");

            // Unload texts
            m_texture_manager.unload("w_title");
            m_texture_manager.unload("w_time");
            m_texture_manager.unload("w_time_played");
            m_texture_manager.unload("w_continue");

            if (!m_model.next_lvl_exists || !m_model.result) {
                m_texture_manager.unload("w_h_title");

                m_texture_manager.unload("w_h_score");

                // Unload texts highscores
                int counter = 0;
                for (auto &highscore : m_model.highscores) {
                    if (counter > 4) {
                        break;
                    }

                    std::string counter_string = std::to_string(counter + 1);
                    m_texture_manager.unload("wh_n_" + counter_string);
                    m_texture_manager.unload("wh_d_" + counter_string);
                    m_texture_manager.unload("wh_s_" + counter_string);

                    counter++;
                }
            }

            // Unload sounds
            m_sound_manager.unload("w_sound");

            // Unsubscribe
            engine::eventbus::eventbus::get_instance().unsubscribe(this);
        }
    }
}
