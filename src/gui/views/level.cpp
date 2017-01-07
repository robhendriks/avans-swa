//
// Created by te on 01-Nov-16.
//

#include <math.h>
#include "level.h"
#include "../../events/object_dropped_on_field.h"
#include "../../events/object_not_dropped_on_field.h"
#include "../../engine/graphics/box_builder.h"
#include "../../utils/string_utils.h"

namespace gui {
    namespace views {

        level::level(in_game_menu &in_game_menu1, level_goals &goals_view, mayor_view &mayor_view1, engine::audio::music_manager &music_manager,
                     models::main_map_model &model, engine::audio::sound_manager &sound_manager)
            : m_in_game_menu(in_game_menu1), m_goals_view(goals_view), m_mayor_view(mayor_view1), m_music_manager(music_manager),
              m_model(model), m_sound_manager(sound_manager),
              m_texture_manager(m_in_game_menu.m_help_view.m_top_bar.m_texture_manager),
              m_color_manager(m_in_game_menu.m_help_view.m_top_bar.m_color_manager),
              m_font_manager(m_in_game_menu.m_help_view.m_top_bar.m_font_manager),
              m_current_page(1), m_speed_factor(1) {}

        void level::before() {
            m_in_game_menu.before();
            m_goals_view.before();
            m_mayor_view.before();

            // Set mayor in mayor_view, but first init it
            auto mayor = m_model.world->get_mayor();
            mayor->init(m_model.world->get_current_level().get_stats().get());
            m_mayor_view.set_mayor(mayor);
            m_mayor_view.set_current_response(mayor->get_fifo_milestone_response());

            // Add callback on menu show
            m_in_game_menu.call_on_show_change([&](bool show) {
                if ((show && !m_model.paused) || (!show && m_model.paused)) {
                    on_pause();
                }
            });

            m_texture_manager.load("images/background-game.png", "background-game");

            // Load textures
            m_texture_manager.load("images/arrows.png", "arrows");
            m_texture_manager.load_from_svg("images/ui-pack.svg", {{1261, 184},
                                                                   {1451, 229}}, 1.5, "l_red_box");
            m_texture_manager.load("images/pause.png", "l_pause");
            m_texture_manager.load("images/play.png", "l_play");
            m_texture_manager.load("images/play_large.png", "l_play_large");

            m_texture_manager.load("images/speed_buttons.png", "l_speed_btns");

            // Load texts
            m_texture_manager.load_text("Resources", {255, 255, 255},
                                        *m_font_manager.get_font("roboto", 25), "l_resources_header_text");

            // Load music
            m_music_manager.load("sounds/game.mp3", "game_bg_music");
            m_music_manager.play("game_bg_music");

            // Add sounds effects
            // First load the sounds
            m_sound_manager.load("sounds/pop.wav", "pop");
            m_sound_manager.load("sounds/error.wav", "error");
            m_sound_manager.load("sounds/victory.wav", "victory");
            m_sound_manager.load("sounds/countdown.wav", "countdown");

            auto &eventbus = engine::eventbus::eventbus::get_instance();

            // Play the pop sound when an object is placed
            std::function<void(events::object_dropped_on_field &)> on_place = [&](
                events::object_dropped_on_field &event) {
                m_sound_manager.play("pop");
            };
            eventbus.subscribe("sound_on_place", on_place);

            // Play the error sound when an object cannot be placed
            std::function<void(events::object_not_dropped_on_field &)> error_place = [&](
                events::object_not_dropped_on_field &event) {
                m_sound_manager.play("error");
            };
            eventbus.subscribe("sound_when_not_placed", error_place);

            // Events subscribe
            eventbus.subscribe(
                dynamic_cast<engine::eventbus::subscriber<engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT>> *>(this));
            eventbus.subscribe(dynamic_cast<engine::eventbus::subscriber<engine::events::key_down> *>(this));
            eventbus.subscribe(dynamic_cast<engine::eventbus::subscriber<events::goal_reached> *>(this));
        }

        void level::on_display_change(engine::math::box2_t display_box) {
            m_in_game_menu.on_display_change(display_box);
            m_goals_view.on_display_change(display_box);
            m_mayor_view.on_display_change(display_box);

            // Create the box for the placeable objects
            float height = 128;
            engine::graphics::box_builder builder1({display_box.width(), height});
            builder1.as_left_bottom(display_box.left_bottom());
            m_placeable_objects_box.reset(new engine::math::box2_t(builder1.build()));

            auto arrow_image_size = engine::math::vec2_t(128, 128);
            // Create the arrow left image box
            engine::graphics::box_builder builder2(arrow_image_size);
            builder2.as_left_top(m_placeable_objects_box->left_top()).add_margin({50, 0})
                .center_vertical(m_placeable_objects_box->min.y, m_placeable_objects_box->max.y);
            m_arrow_left_box.reset(new engine::math::box2_t(builder2.build()));

            // Create the arrow right image box
            engine::graphics::box_builder builder3(arrow_image_size);
            builder3.as_right_top(m_placeable_objects_box->right_top()).add_margin({-50, 0})
                .center_vertical(m_placeable_objects_box->min.y, m_placeable_objects_box->max.y);
            m_arrow_right_box.reset(new engine::math::box2_t(builder3.build()));

            // Calculate the pages
            float x_per_object = m_model.world->get_current_level().get_map()->get_tile_size().x + 50;
            float x_space = m_placeable_objects_box->width() - m_arrow_left_box->max.x -
                            (m_placeable_objects_box->max.x - m_arrow_right_box->min.x) - 50;
            m_objects_per_page = static_cast<int>(floor(x_space / x_per_object));
            int total_objects = m_model.world->get_current_level().get_placeable_objects().size();
            m_pages = static_cast<int>(ceil(static_cast<float>(total_objects) / m_objects_per_page));
            if (m_current_page > m_pages) {
                m_current_page = m_pages;
            }

            // Set the draw boxes for the placeable objects
            update_placeable_objects_page();
            // Create the box for the map
            engine::graphics::box_builder builder5({display_box.width(),
                                                    display_box.height() -
                                                    m_in_game_menu.m_help_view.m_top_bar.m_bar_box->height() -
                                                    m_placeable_objects_box->height()});
            builder5.as_left_top(m_in_game_menu.m_help_view.m_top_bar.m_bar_box->left_top());
            m_model.world->get_current_level().get_map()->set_display_box(builder5.build());

            // Reposition the goals box
            engine::graphics::box_builder builder6(m_goals_view.m_stats_header_box->size());
            builder6.as_right_top(m_in_game_menu.m_help_view.m_top_bar.m_bar_box->right_bottom())
                .add_margin({-80, 80});
            m_goals_view.m_stats_header_box.reset(new engine::math::box2_t(builder6.build()));

            // Countdown box
            engine::graphics::box_builder builder7(m_goals_view.m_stats_header_box->size());
            builder7.as_left_top(m_in_game_menu.m_help_view.m_top_bar.m_bar_box->left_bottom()).add_margin(
                {80, 80});

            if (m_model.world->get_current_level().get_max_duration() > 0) {
                m_countdown_box.reset(new engine::math::box2_t(builder7.build()));
            } else {
                builder7.add_margin({-m_goals_view.m_stats_header_box->width(),
                                     -m_goals_view.m_stats_header_box->height() - 20});
                m_countdown_box.reset(new engine::math::box2_t(builder7.build()));
            }

            // Set the pause box
            engine::graphics::box_builder builder8(m_texture_manager.get_size("l_pause"));
            builder8.as_left_top(m_in_game_menu.m_question_mark_icon_box->right_top()).add_margin({5, 0});
            m_pause_box.reset(new engine::math::box2_t(builder8.build()));

            // Set the slow down box
            engine::graphics::box_builder builder9({32, 32});
            builder9.as_left_top(m_pause_box->right_top()).add_margin({5, 0});
            m_slow_down_box.reset(new engine::math::box2_t(builder9.build()));

            // Set the fast forward box
            engine::graphics::box_builder builder13({32, 32});
            builder13.as_left_top(m_slow_down_box->right_top()).add_margin({5, 0});
            m_fast_forward_box.reset(new engine::math::box2_t(builder13.build()));

            // Set the overlay resume box
            engine::graphics::box_builder builder10(
                m_in_game_menu.m_help_view.m_top_bar.m_texture_manager.get_size("l_play_large"));
            builder10.to_center(*m_in_game_menu.m_help_view.m_overlay_box);
            m_overlay_resume_box.reset(new engine::math::box2_t(builder10.build()));

            // Resources header box
            engine::graphics::box_builder builder11(m_goals_view.m_stats_header_box->size());
            builder11.as_left_top(m_countdown_box->left_bottom()).add_margin({0, 20});
            m_resources_header_box.reset(new engine::math::box2_t(builder11.build()));

            // Resources header text box
            engine::graphics::box_builder builder12(m_texture_manager.get_size("l_resources_header_text"));
            builder12.to_center(*m_resources_header_box);
            m_resources_header_text_box.reset(new engine::math::box2_t(builder12.build()));
        }

        void level::update_placeable_objects_page() {
            engine::math::box2_t box_for_hidden_object({-1, -1}, {-1, -1});

            // Set the boxes for the placeable objects
            engine::graphics::box_builder builder4(m_model.world->get_current_level().get_map()->get_tile_size());
            builder4.as_left_top(m_arrow_left_box->right_top())
                .center_vertical(m_placeable_objects_box->min.y, m_placeable_objects_box->max.y);

            int object_counter = 0;
            int page_counter = 1;
            for (auto &obj : m_model.world->get_current_level().get_placeable_objects()) {
                // Page check
                if (object_counter == m_objects_per_page) {
                    object_counter = 0;
                    page_counter++;
                }

                // Set the object box
                if (page_counter == m_current_page) {
                    builder4.add_margin({50, 0});
                    obj->set_box(std::make_shared<engine::math::box2_t>(builder4.build()));
                    builder4.add_margin({m_model.world->get_current_level().get_map()->get_tile_size().x, 0});
                } else {
                    obj->set_box(std::make_shared<engine::math::box2_t>(box_for_hidden_object));
                }

                // Count the objects (for the page)
                object_counter++;
            }
        }

        void level::draw(unsigned int time_elapsed, engine::math::box2_t display_box) {
            auto current_level = m_model.world->get_current_level();

            if (current_level.is_game_over(time_elapsed) ||
                current_level.is_goal_reached()) {
                m_controller->show();
            }

            m_texture_manager.draw("background-game", display_box);

            // With the pause or play btn
            m_texture_manager.draw(m_model.paused ? "l_play" : "l_pause", *m_pause_box);

            // Draw the slow down and fast forward buttons
            float sd_y_offset = can_decrease_speed() ? 0 : 32;
            float ff_y_offset = can_increase_speed() ? 0 : 32;
            m_texture_manager.draw("l_speed_btns", {32, sd_y_offset}, *m_slow_down_box);
            m_texture_manager.draw("l_speed_btns", {0, ff_y_offset}, *m_fast_forward_box);

            // Draw the speed text
            std::string factor = std::to_string(m_speed_factor);
            m_texture_manager.load_text(factor.substr(0, 5) + "x", {0, 255, 0},
                                        *m_font_manager.get_font("roboto", 18), "l_speed");

            engine::graphics::box_builder speed_builder(m_texture_manager.get_size("l_speed"));
            speed_builder.as_left_top(m_fast_forward_box->right_top()).add_margin({5, 0})
                .center_vertical(m_fast_forward_box->min.y, m_fast_forward_box->max.y);

            m_texture_manager.draw("l_speed", speed_builder.build());
            m_texture_manager.unload("l_speed");

            // Draw the goals
            m_goals_view.draw(time_elapsed, display_box);

            // Draw the map
            current_level.get_map()->draw(m_in_game_menu.m_help_view.m_top_bar.m_draw_managers, time_elapsed);

            // Draw the mayor_view
            m_mayor_view.draw(time_elapsed, display_box);

            // Draw the arrows
            float left_arrow_y = (m_current_page == 1 ? 128 : 0);
            m_texture_manager.draw("arrows", {0, left_arrow_y}, *m_arrow_left_box);
            float right_arrow_y = (m_current_page == m_pages ? 128 : 0);
            m_texture_manager.draw("arrows", {128, right_arrow_y}, *m_arrow_right_box);

            // Draw the placeable objects
            for (auto &obj : current_level.get_placeable_objects()) {
                obj->draw(m_in_game_menu.m_help_view.m_top_bar.m_draw_managers, time_elapsed);
            }

            // Draw resources header
            m_texture_manager.draw("g_header", *m_resources_header_box);
            m_texture_manager.draw("l_resources_header_text", *m_resources_header_text_box);

            // Draw each resource
            engine::graphics::box_builder builder1(m_resources_header_box->size());
            builder1.as_left_top(m_resources_header_box->left_bottom());
            int resource_counter =0;
            for (auto resource : m_model.world->get_current_level().get_resources()) {
                builder1.add_margin({0, 20});
                m_texture_manager.draw("g_box", builder1.build());

                // Load the resource text
                std::string resource_type =resource->get_resource_type();
                resource_type[0] = toupper(resource_type[0]);
                //Build second part of the string
                std::string optional_increment ="";

                if(m_model.previous_resource.size() != 0 && m_model.previous_resource[resource_counter]->get_count() < resource->get_count()){
                    optional_increment =" (+ "+std::to_string(resource->get_count() - m_model.previous_resource[resource_counter]->get_count())+")";

                }
                m_texture_manager.load_text(resource_type + ": " + std::to_string(resource->get_count())+optional_increment, {0, 0, 0},
                    *m_font_manager.get_font("roboto", 25), "l_resource");


                engine::graphics::box_builder builder2(m_texture_manager.get_size("l_resource"));
                builder2.to_center(builder1.build());
                m_texture_manager.draw("l_resource", builder2.build());

                // Unload text
                m_texture_manager.unload("l_resource");

                builder1.add_margin({0, m_resources_header_box->height()});
                resource_counter++;
            }

            // Draw the countdown when needed
            if (current_level.get_max_duration() > 0) {
                // Calculate time left
                int level_time = time_elapsed - current_level.get_start_time();
                unsigned int time_left = static_cast<unsigned int>(current_level.get_max_duration() - level_time);

                engine::graphics::color4_t color{0, 0, 0};
                if (time_left <= 53200) {
                    // Play countdown music
                    // First stop the bg music
                    m_music_manager.stop();
                    m_sound_manager.play_if("countdown", true, NULL, 128, 400);

                    m_texture_manager.draw("l_red_box", *m_countdown_box);

                    color = {255, 255, 255};
                } else {
                    m_texture_manager.draw("g_box", *m_countdown_box);
                }

                m_texture_manager.load_text(utils::string_utils::ms_to_hms(time_left), color,
                                            *m_font_manager.get_font("roboto", 25), "l_countdown");
                engine::graphics::box_builder builder(m_texture_manager.get_size("l_countdown"));
                builder.to_center(*m_countdown_box);
                m_texture_manager.draw("l_countdown", builder.build());
                m_texture_manager.unload("l_countdown");
            }

            // Draw enemies
            for (auto &enemy : current_level.get_enemies_in_lvl()) {
                enemy->draw(m_in_game_menu.m_help_view.m_top_bar.m_draw_managers, time_elapsed);
            }

            // Draw overflow on pause
            if (m_model.paused && !m_in_game_menu.m_show && !m_in_game_menu.m_help_view.m_show) {
                m_color_manager.draw({0, 0, 0, 180}, *m_in_game_menu.m_help_view.m_overlay_box);

                // Draw resume btn in the center of the overlay
                m_texture_manager.draw("l_play_large", *m_overlay_resume_box);
            }

            // Draw the in game menu as last because of the overlay
            m_in_game_menu.draw(time_elapsed, display_box);

            m_controller->update();
        }

        void level::on_event(engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT> &event) {
            engine::math::vec2_t *position = engine::input::input_handler::get_instance()->get_mouse_position();

            if (m_pause_box->contains(*position) ||
                (m_model.paused && !m_in_game_menu.m_show && !m_in_game_menu.m_help_view.m_show &&
                 m_overlay_resume_box->contains(*position))) {
                m_in_game_menu.m_show = false;
                m_in_game_menu.m_help_view.m_show = false;
                on_pause();
            } else if (!m_model.paused) {
                // Only if not paused
                if (m_arrow_left_box->contains(*position)) {
                    navigate_left();
                } else if (m_arrow_right_box->contains(*position)) {
                    navigate_right();
                } else if (m_slow_down_box->contains(*position)) {
                    decrease_speed();
                } else if (m_fast_forward_box->contains(*position)) {
                    increase_speed();
                }
            }
        }

        void level::on_event(engine::events::key_down &event) {
            if (!m_in_game_menu.m_show) {
                if (event.get_keycode() == engine::input::keycodes::keycode::PAUSE ||
                    (m_model.paused && event.get_keycode() == engine::input::keycodes::keycode::ENTER)) {
                    on_pause();
                } else if (!m_model.paused) {
                    if (event.get_keycode() == engine::input::keycodes::keycode::LEFT) {
                        navigate_left();
                    } else if (event.get_keycode() == engine::input::keycodes::keycode::RIGHT) {
                        navigate_right();
                    } else if (event.get_keycode() == engine::input::keycodes::keycode::PAGEUP) {
                        increase_speed();
                    } else if (event.get_keycode() == engine::input::keycodes::keycode::PAGEDOWN) {
                        decrease_speed();
                    } else if (event.get_keycode() == engine::input::keycodes::keycode::HOME) {
                        reset_speed();
                    } else if(event.get_keycode() == engine::input::keycodes::keycode::F){
                        m_model.world->get_current_level().execute_cheat();
                    }
                }
            }
        }

        void level::reset_speed() {
            if (m_speed_factor != 1) {
                m_in_game_menu.m_help_view.m_top_bar.m_engine.reset_speed();
                m_speed_factor = 1;
            }
        }

        bool level::can_increase_speed() {
            return m_speed_factor < (3 * 2);
        }

        void level::increase_speed() {
            // Check if it can be increased more
            if (can_increase_speed()) {
                m_in_game_menu.m_help_view.m_top_bar.m_engine.change_game_speed(2);
                m_speed_factor *= 2;
            }
        }

        bool level::can_decrease_speed() {
            return m_speed_factor > (0.5 * 0.5 * 0.5);
        }

        void level::decrease_speed() {
            // Check if it can be decreased more
            if (can_decrease_speed()) {
                m_in_game_menu.m_help_view.m_top_bar.m_engine.change_game_speed(0.5);
                m_speed_factor *= 0.5;
            }
        }

        void level::navigate_left() {
            if (m_current_page > 1) {
                m_current_page--;
                update_placeable_objects_page();
            }
        }

        void level::navigate_right() {
            if (m_current_page < m_pages) {
                m_current_page++;
                update_placeable_objects_page();
            }
        }

        void level::on_event(events::goal_reached &event) {
            if (!m_model.paused) {
                m_sound_manager.play("victory");
            }
        }

        void level::after() {
            m_in_game_menu.after();
            m_goals_view.after();
            m_mayor_view.after();

            m_texture_manager.unload("background-game");

            // Unload textures
            m_texture_manager.unload("arrows");
            m_texture_manager.unload("l_red_box");
            m_texture_manager.unload("l_pause");
            m_texture_manager.unload("l_play");
            m_texture_manager.unload("l_speed_btns");

            // Unload texts
            m_texture_manager.unload("l_resources_header_text");

            // Unload the music
            m_music_manager.unload("game_bg_music");

            // Remove sound listeners
            auto &eventbus = engine::eventbus::eventbus::get_instance();
            eventbus.unsubscribe("sound_on_place");
            eventbus.unsubscribe("sound_when_not_placed");

            // Unload sounds
            m_sound_manager.unload("pop");
            m_sound_manager.unload("error");
            m_sound_manager.unload("victory");
            m_sound_manager.unload("countdown");

            // Event click unsubscribe
            eventbus.unsubscribe(
                dynamic_cast<engine::eventbus::subscriber<engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT>> *>(this));
            eventbus.unsubscribe(dynamic_cast<engine::eventbus::subscriber<engine::events::key_down> *>(this));
            eventbus.unsubscribe(dynamic_cast<engine::eventbus::subscriber<events::goal_reached> *>(this));

            // Make sure the engine is running (so animations will work)
            m_controller->resume_engine_if();
        }

        void level::set_controller(controllers::main_map_controller &controller) {
            m_controller = &controller;
        }

        void level::on_pause() {
            m_controller->pause(); // Will pause or resume the game

            if (m_model.paused) {
                // Reset the speed factor
                m_speed_factor = 1;
                // Pause the music
                m_music_manager.pause();
                // Pause all sounds
                m_sound_manager.pause_all();
            } else {
                // Resume all music
                m_music_manager.resume();
                // Resume all sounds
                m_sound_manager.resume_all();
            };
        }
    }
}
