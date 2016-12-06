//
// Created by te on 19-Nov-16.
//

#include "win_game_over.h"
#include "../../engine/graphics/box_builder.h"
#include "../../utils/string_utils.h"

namespace gui {
    namespace views {

        win_game_over::win_game_over(top_bar &top_bar1, level_goals &goals_view, models::transition_level_model &model,
            engine::audio::sound_manager &sound_manager) :
                m_top_bar(top_bar1), m_goals_view(goals_view), m_controller(nullptr), m_model(model),
                m_sound_manager(sound_manager) {

        }

        void win_game_over::before() {
            m_top_bar.before();
            m_goals_view.before();

            // Load textures
            m_top_bar.m_texture_manager.load_from_svg("images/ui-pack.svg", {{1261, 124}, {1451, 169}}, 2, "w_green_box");
            m_top_bar.m_texture_manager.load_from_svg("images/ui-pack.svg", {{1261, 184}, {1451, 229}}, 1.5, "w_red_box");
            m_top_bar.m_texture_manager.load_from_svg("images/ui-pack.svg", {{1080, 630}, {1119, 661}}, 0.8, "red_slider_right");

            // Load texts
            std::string result = m_model.result ? "Victory" : "Defeat";
            std::string last = m_model.next_lvl_exists ? "" : " - last level";
            m_top_bar.m_texture_manager.load_text(result + last, {255, 193, 132}, *m_goals_view.m_font_manager.get_font("roboto", 50), "w_title");

            m_top_bar.m_texture_manager.load_text("Duration", {255, 255, 255}, *m_goals_view.m_font_manager.get_font("roboto", 25), "w_time");
            m_top_bar.m_texture_manager.load_text(utils::string_utils::ms_to_hms(m_model.duration), {0, 0, 0}, *m_goals_view.m_font_manager.get_font("roboto", 25), "w_time_played");
            m_top_bar.m_texture_manager.load_text("Continue", {255, 255, 255}, *m_goals_view.m_font_manager.get_font("roboto", 25), "w_continue");

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
            m_top_bar.on_display_change(display_box);
            m_goals_view.on_display_change(display_box);

            // Create title box
            engine::graphics::box_builder builder1(m_top_bar.m_texture_manager.get_size("w_title"));
            builder1.as_left_top(m_top_bar.m_bar_box->left_bottom()).add_margin({0, 40})
                .center_horizontal(m_top_bar.m_bar_box->min.x, m_top_bar.m_bar_box->max.x);
            m_title_box.reset(new engine::math::box2_t(builder1.build()));

            // Create the continue box
            engine::graphics::box_builder builder2(m_top_bar.m_texture_manager.get_size("w_green_box"));
            builder2.as_right_bottom(display_box.right_bottom()).add_margin({-150, -150});
            m_continue_box.reset(new engine::math::box2_t(builder2.build()));

            // Create continue text box
            engine::graphics::box_builder builder3(m_top_bar.m_texture_manager.get_size("w_continue"));
            builder3.as_left_top(m_continue_box->left_top()).add_margin({20, 10});
            m_continue_text_box.reset(new engine::math::box2_t(builder3.build()));

            // Create the slider move boxes
            auto slider_size = m_top_bar.m_texture_manager.get_size("red_slider_right");

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

            auto time_header_size = m_top_bar.m_texture_manager.get_size("w_red_box");
            auto stats_header_size = m_goals_view.m_stats_header_box->size();

            // Stats wrapper box
            engine::graphics::box_builder builder11(time_header_size + stats_header_size + 50);
            builder11.as_left_top(m_title_box->left_bottom())
                .center_horizontal(m_title_box->min.x, m_title_box->max.x)
                .center_vertical(m_title_box->max.y, m_continue_box->min.y).add_margin({0, -100});
            auto wrapper_box = builder11.build();

            // Create the time header box
            engine::graphics::box_builder builder7(time_header_size);
            builder7.as_left_top(wrapper_box.left_top());
            m_time_header_box.reset(new engine::math::box2_t(builder7.build()));

            // Create the time header text box
            engine::graphics::box_builder builder8(m_top_bar.m_texture_manager.get_size("w_time"));
            builder8.to_center(*m_time_header_box);
            m_time_header_text_box.reset(new engine::math::box2_t(builder8.build()));

            // Create the time box
            engine::graphics::box_builder builder9(m_top_bar.m_texture_manager.get_size("g_box"));
            builder9.as_left_top(m_time_header_box->left_bottom()).add_margin({0, 10});
            m_time_box.reset(new engine::math::box2_t(builder9.build()));

            // Create the time text box
            engine::graphics::box_builder builder10(m_top_bar.m_texture_manager.get_size("w_time_played"));
            builder10.to_center(*m_time_box);
            m_time_text_box.reset(new engine::math::box2_t(builder10.build()));

            // Reposition the goals box
            engine::graphics::box_builder builder6(stats_header_size);
            builder6.as_right_top(wrapper_box.right_top());
            m_goals_view.m_stats_header_box.reset(new engine::math::box2_t(builder6.build()));
        }

        void win_game_over::draw(unsigned int time_elapsed, engine::math::box2_t display_box) {
            m_top_bar.draw(time_elapsed, display_box);
            m_goals_view.draw(time_elapsed, display_box);

            m_top_bar.m_texture_manager.draw("w_title", *m_title_box);
            m_top_bar.m_texture_manager.draw("w_red_box", *m_time_header_box);
            m_top_bar.m_texture_manager.draw("w_time", *m_time_header_text_box);
            m_top_bar.m_texture_manager.draw("g_box", *m_time_box);
            m_top_bar.m_texture_manager.draw("w_time_played", *m_time_text_box);
            m_top_bar.m_texture_manager.draw("w_green_box", *m_continue_box);
            m_top_bar.m_texture_manager.draw("w_continue", *m_continue_text_box);

            m_moveable_slider_box->move(time_elapsed);
            for (auto &box : m_moveable_slider_box->get_boxes()) {
                if (m_continue_slider_box->contains(box)) {
                    m_top_bar.m_texture_manager.draw("red_slider_right", box);
                } else {
                    if (m_continue_slider_box->contains(box.min)) {
                        auto show_box = engine::math::box2_t(box.min, m_continue_slider_box->max);
                        m_top_bar.m_texture_manager.draw("red_slider_right", {0, 0}, show_box);
                    } else if (m_continue_slider_box->contains(box.max)) {
                        auto show_box = engine::math::box2_t(m_continue_slider_box->min, box.max);
                        m_top_bar.m_texture_manager.draw("red_slider_right", {show_box.min.x - box.min.x, 0}, show_box);
                    }
                }
            }
        }

        void win_game_over::on_event(engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT> &event) {
            engine::math::vec2_t *position = engine::input::input_handler::get_instance()->get_mouse_position();

            if (m_continue_box->contains(*position)) {
                m_controller->next_lvl();
            }
        }

        void win_game_over::set_controller(gui::controllers::main_map_controller &controller) {
            m_controller = &controller;
        }

        void win_game_over::after() {
            m_top_bar.after();
            m_goals_view.after();

            // Unload textures
            m_top_bar.m_texture_manager.unload("w_green_box");
            m_top_bar.m_texture_manager.unload("w_red_box");
            m_top_bar.m_texture_manager.unload("red_slider_right");

            // Unload texts
            m_top_bar.m_texture_manager.unload("w_title");
            m_top_bar.m_texture_manager.unload("w_time");
            m_top_bar.m_texture_manager.unload("w_time_played");
            m_top_bar.m_texture_manager.unload("w_continue");

            // Unload sounds
            m_sound_manager.unload("w_sound");

            // Unsubscribe
            engine::eventbus::eventbus::get_instance().unsubscribe(this);
        }
    }
}
