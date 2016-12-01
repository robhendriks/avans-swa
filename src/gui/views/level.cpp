//
// Created by te on 01-Nov-16.
//

#include <math.h>
#include "level.h"
#include "../../events/object_placed_on_field.h"
#include "../../events/object_cannot_be_placed_on_field.h"
#include "../../engine/graphics/box_builder.h"

namespace gui {
    namespace views {

        level::level(top_bar &top_bar1, engine::audio::music_manager &music_manager,
                     engine::window &window, models::main_map_model &model, engine::audio::sound_manager &sound_manager)
            : m_top_bar(top_bar1), m_music_manager(music_manager), m_window(window), m_model(model),
              m_sound_manager(sound_manager), m_current_page(1) {
        }

        void level::before() {
            m_top_bar.before();

            // Load arrow textures
            m_top_bar.m_texture_manager.load("images/arrow-left.png", "arrow-left");
            m_top_bar.m_texture_manager.load("images/arrow-right.png", "arrow-right");

            // Load music
            m_music_manager.load("sounds/game.mp3", "game_bg_music");
            m_music_manager.play("game_bg_music");

            // Add sounds effects
            // First load the sounds
            m_sound_manager.load("sounds/pop.wav", "pop");
            m_sound_manager.load("sounds/error.wav", "error");
            auto &eventbus = engine::eventbus::eventbus::get_instance();

            // Play the pop sound when an object is placed
            std::function<void(events::object_placed_on_field &)> on_place = [&](
                events::object_placed_on_field &event) {
                m_sound_manager.play("pop");
            };
            eventbus.subscribe("sound_on_place", on_place);

            // Play the error sound when an object cannot be placed
            std::function<void(events::object_cannot_be_placed_on_field &)> error_place = [&](
                events::object_cannot_be_placed_on_field &event) {
                m_sound_manager.play("error");
            };
            eventbus.subscribe("sound_when_not_placed", error_place);

            // Event click subscribe
            eventbus.subscribe(this);
        }

        void level::on_display_change(engine::math::box2_t display_box) {
            m_top_bar.on_display_change(display_box);

            // Create the box for the placeable objects
            float height = 128;
            engine::graphics::box_builder builder1({display_box.width(), height});
            builder1.as_left_bottom(display_box.left_bottom());
            m_placeable_objects_box.reset(new engine::math::box2_t(builder1.build()));

            // Create the arrow left image box
            auto arrow_left_image_size = m_top_bar.m_texture_manager.get_size("arrow-left");
            engine::graphics::box_builder builder2(arrow_left_image_size);
            builder2.as_left_top(m_placeable_objects_box->left_top()).add_margin({50, 0})
                .center_vertical(m_placeable_objects_box->min.y, m_placeable_objects_box->max.y);
            m_arrow_left_box.reset(new engine::math::box2_t(builder2.build()));

            // Create the arrow right image box
            auto arrow_right_image_size = m_top_bar.m_texture_manager.get_size("arrow-right");
            engine::graphics::box_builder builder3(arrow_right_image_size);
            builder3.as_right_top(m_placeable_objects_box->right_top()).add_margin({-50, 0})
                .center_vertical(m_placeable_objects_box->min.y, m_placeable_objects_box->max.y);
            m_arrow_right_box.reset(new engine::math::box2_t(builder3.build()));

            // Calculate the pages
            float x_per_object = m_model.world->get_current_level().get_map()->get_tile_size().x + 50;
            float x_space = m_placeable_objects_box->width() - m_arrow_left_box->width() - m_arrow_right_box->width();
            m_objects_per_page = static_cast<int>(floor(x_space / x_per_object));
            int total_objects = m_model.world->get_current_level().get_placeable_objects().size();
            m_pages = static_cast<int>(floor(total_objects / m_objects_per_page));
            if (m_current_page < m_pages) {
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
                } else {
                    obj->set_box(box_for_hidden_object);
                }

                // Count the objects (for the page)
                object_counter++;
            }
        }

        void level::draw(unsigned int time_elapsed, engine::math::box2_t display_box) {
            m_top_bar.draw(time_elapsed, display_box);

            if (m_model.world->get_current_level().is_game_over(time_elapsed) ||
                m_model.world->get_current_level().is_goal_reached()) {
                m_controller->show();
            }

            // draw enemies
            for(auto enemy : m_model.world->get_current_level().get_enemies_in_lvl())
                enemy->draw(m_top_bar.m_texture_manager , time_elapsed);

            // Draw the map
            m_model.world->get_current_level().get_map()->draw(m_top_bar.m_texture_manager, time_elapsed);

            // Draw the arrows
            m_top_bar.m_texture_manager.draw("arrow-left", {0, 0}, *m_arrow_left_box);
            m_top_bar.m_texture_manager.draw("arrow-right", {0, 0}, *m_arrow_right_box);

            // Draw the placeable objects
            for (auto &obj : m_model.world->get_current_level().get_placeable_objects()) {
                obj->draw(m_top_bar.m_texture_manager, time_elapsed);
            }
        }

        void level::on_event(engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT> &event) {
            engine::math::vec2_t *position = engine::input::input_handler::get_instance()->get_mouse_position();

            if (m_arrow_left_box->contains(*position)) {
                if (m_current_page > 1) {
                    m_current_page--;
                    update_placeable_objects_page();
                }
            } else if (m_arrow_right_box->contains(*position)) {
                if (m_current_page < m_pages) {
                    m_current_page++;
                    update_placeable_objects_page();
                }
            }
        }

        void level::after() {
            m_top_bar.after();

            // Unload arrow textures
            m_top_bar.m_texture_manager.unload("arrow-left");
            m_top_bar.m_texture_manager.unload("arrow-right");

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

            // Event click unsubscribe
            eventbus.unsubscribe(this);
        }

        void level::set_controller(controllers::main_map_controller &controller) {
            m_controller = &controller;
        }
    }
}
