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

        level::level(top_bar &top_bar1, level_goals &goals_view, engine::audio::music_manager &music_manager,
                     engine::window &window, models::main_map_model &model, engine::audio::sound_manager &sound_manager)
            : m_top_bar(top_bar1), m_goals_view(goals_view), m_music_manager(music_manager), m_window(window),
              m_model(model), m_sound_manager(sound_manager), m_current_page(1) {
        }

        void level::before() {
            m_top_bar.before();
            m_goals_view.before();

            // Load arrow textures
            m_top_bar.m_texture_manager.load("images/arrows.png", "arrows");
            m_top_bar.m_texture_manager.load_from_svg("images/ui-pack.svg", {{1261, 184}, {1451, 229}}, 1.5, "l_red_box");
            m_top_bar.m_texture_manager.load("images/pause.png", "l_pause");
            m_top_bar.m_texture_manager.load("images/play.png", "l_play");
            m_top_bar.m_texture_manager.load("images/play_large.png", "l_play_large");

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
            eventbus.subscribe(dynamic_cast<engine::eventbus::subscriber<engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT>>*>(this));
            eventbus.subscribe(dynamic_cast<engine::eventbus::subscriber<engine::events::key_down>*>(this));
            eventbus.subscribe(dynamic_cast<engine::eventbus::subscriber<events::goal_reached>*>(this));
        }

        void level::on_display_change(engine::math::box2_t display_box) {
            m_top_bar.on_display_change(display_box);
            m_goals_view.on_display_change(display_box);

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
                                                    display_box.height() - m_top_bar.m_bar_box->height() -
                                                    m_placeable_objects_box->height()});
            builder5.as_left_top(m_top_bar.m_bar_box->left_top());
            m_model.world->get_current_level().get_map()->set_display_box(builder5.build());

            // Reposition the goals box
            engine::graphics::box_builder builder6(m_goals_view.m_stats_header_box->size());
            builder6.as_right_top(m_top_bar.m_bar_box->right_bottom())
                .add_margin({-80, 80});
            m_goals_view.m_stats_header_box.reset(new engine::math::box2_t(builder6.build()));

            if (m_model.world->get_current_level().get_max_duration() > 0) {
                // Countdown
                engine::graphics::box_builder builder7(m_goals_view.m_stats_header_box->size());
                builder7.as_left_top(m_top_bar.m_bar_box->left_bottom()).add_margin({80, 80});
                m_countdown_box.reset(new engine::math::box2_t(builder7.build()));
            }

            // Set the pause box
            engine::graphics::box_builder builder8(m_top_bar.m_texture_manager.get_size("l_pause"));
            builder8.as_left_top(m_top_bar.m_bar_box->left_top()).add_margin({50, 0});
            m_pause_box.reset(new engine::math::box2_t(builder8.build()));

            // Set the overlay box
            engine::graphics::box_builder builder9(display_box.size() - engine::math::vec2_t{0, m_top_bar.m_bar_box->height()});
            builder9.as_left_top(m_top_bar.m_bar_box->left_bottom());
            m_overlay_box.reset(new engine::math::box2_t(builder9.build()));

            // Set the overlay resume box
            engine::graphics::box_builder builder10(m_top_bar.m_texture_manager.get_size("l_play_large"));
            builder10.to_center(*m_overlay_box);
            m_overlay_resume_box.reset(new engine::math::box2_t(builder10.build()));
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
                    obj->set_box(builder4.build());
                    builder4.add_margin({m_model.world->get_current_level().get_map()->get_tile_size().x, 0});
                } else {
                    obj->set_box(box_for_hidden_object);
                }

                // Count the objects (for the page)
                object_counter++;
            }
        }

        void level::draw(unsigned int time_elapsed, engine::math::box2_t display_box) {
            auto current_level = m_model.world->get_current_level();
            m_controller->update();

            if (current_level.is_game_over(time_elapsed) ||
                current_level.is_goal_reached()) {
                m_controller->show();
            }

            // Draw the top bar
            m_top_bar.draw(time_elapsed, display_box);
            // With the pause or play btn
            m_top_bar.m_texture_manager.draw(m_model.paused ? "l_play" : "l_pause", *m_pause_box);

            // Draw the goals
            m_goals_view.draw(time_elapsed, display_box);

            // draw enemies
//            for(auto &enemy : m_model.world->get_current_level().get_enemies_in_lvl()) {
                //enemy->draw(m_top_bar.m_texture_manager, time_elapsed);
  //          }

            // Draw the map
            current_level.get_map()->draw(m_top_bar.m_texture_manager, time_elapsed);

            // Draw the arrows
            float left_arrow_y = (m_current_page == 1 ? 128 : 0);
            m_top_bar.m_texture_manager.draw("arrows", {0, left_arrow_y}, *m_arrow_left_box);
            float right_arrow_y = (m_current_page == m_pages ? 128 : 0);
            m_top_bar.m_texture_manager.draw("arrows", {128, right_arrow_y}, *m_arrow_right_box);

            // Draw the placeable objects
            for (auto &obj : current_level.get_placeable_objects()) {
                obj->draw(m_top_bar.m_texture_manager, time_elapsed);
            }

            if (current_level.get_max_duration() > 0) {
                // Draw the countdown

                // Calculate time left
                int level_time = time_elapsed - current_level.get_start_time();
                unsigned int time_left = static_cast<unsigned int>(current_level.get_max_duration() - level_time);

                engine::graphics::color4_t color{0, 0, 0};
                if (time_left <= 53200) {
                    // Play countdown music
                    // First stop the bg music
                    m_music_manager.stop();
                    m_sound_manager.play_if("countdown", true, NULL, 128, 400);

                    m_top_bar.m_texture_manager.draw("l_red_box", *m_countdown_box);

                    color = {255, 255, 255};
                } else {
                    m_top_bar.m_texture_manager.draw("g_box", *m_countdown_box);
                }

                m_top_bar.m_texture_manager.load_text(utils::string_utils::ms_to_hms(time_left), color,
                                                      *m_goals_view.m_font_manager.get_font("roboto", 25), "l_countdown");
                engine::graphics::box_builder builder(m_top_bar.m_texture_manager.get_size("l_countdown"));
                builder.to_center(*m_countdown_box);
                m_top_bar.m_texture_manager.draw("l_countdown", builder.build());
                m_top_bar.m_texture_manager.unload("l_countdown");
            }

            // Draw overflow on pause
            if (m_model.paused) {
                m_top_bar.m_color_manager.draw({0, 0, 0, 180}, *m_overlay_box);

                // Draw resume btn in the center of the overlay
                m_top_bar.m_texture_manager.draw("l_play_large", *m_overlay_resume_box);
            }
        }

        void level::on_event(engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT> &event) {
            engine::math::vec2_t *position = engine::input::input_handler::get_instance()->get_mouse_position();

            if (m_pause_box->contains(*position) || m_overlay_resume_box->contains(*position)) {
                on_pause();
            } else if (!m_model.paused) {
                // Only if not paused
                if (m_arrow_left_box->contains(*position)) {
                    navigate_left();
                } else if (m_arrow_right_box->contains(*position)) {
                    navigate_right();
                }
            }
        }

        void level::on_event(engine::events::key_down &event) {
            if (event.get_keycode() == engine::input::keycodes::keycode::PAUSE ||
                event.get_keycode() == engine::input::keycodes::keycode::ENTER) {
                on_pause();
            } else if (!m_model.paused) {
                if (event.get_keycode() == engine::input::keycodes::keycode::LEFT) {
                    navigate_left();
                } else if (event.get_keycode() == engine::input::keycodes::keycode::RIGHT) {
                    navigate_right();
                }
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
            m_top_bar.after();
            m_goals_view.after();

            // Unload arrow textures
            m_top_bar.m_texture_manager.unload("arrows");
            m_top_bar.m_texture_manager.unload("l_red_box");
            m_top_bar.m_texture_manager.unload("l_pause");
            m_top_bar.m_texture_manager.unload("l_play");

            // can be done by the objects as well
            m_model.world->unload(m_top_bar.m_texture_manager);

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
            eventbus.unsubscribe(dynamic_cast<engine::eventbus::subscriber<engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT>>*>(this));
            eventbus.unsubscribe(dynamic_cast<engine::eventbus::subscriber<engine::events::key_down>*>(this));
            eventbus.unsubscribe(dynamic_cast<engine::eventbus::subscriber<events::goal_reached>*>(this));
        }

        void level::set_controller(controllers::main_map_controller &controller) {
            m_controller = &controller;
        }

        void level::on_pause() {
            m_controller->pause(); // Will pause or resume the game

            if (m_model.paused) {
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
