//
// Created by te on 01-Nov-16.
//

#include "main_map.h"
#include "../../engine/input/input_handler.h"
#include "../../engine/eventbus/eventbus.h"
#include "../../events/object_placed_on_field.h"
#include "../../events/object_cannot_be_placed_on_field.h"

namespace gui {
    namespace views {

        main_map::main_map(engine::graphics::texture_manager &texture_manager, engine::audio::music_manager &music_manager,
                           engine::window &window, models::main_map_model &model, engine::audio::sound_manager &sound_manager)
            : m_texture_manager(texture_manager), m_music_manager(music_manager), m_window(window), m_model(model),
            m_sound_manager(sound_manager) {
        }

        void main_map::before() {
            // Load music
            m_music_manager.load("sounds/game.mp3", "game_bg_music");
            m_music_manager.play("game_bg_music");

            // Add sounds effects
            // First load the sounds
            m_sound_manager.load("sounds/pop.wav", "pop");
            m_sound_manager.load("sounds/error.wav", "error");
            auto &eventbus = engine::eventbus::eventbus::get_instance();

            // Play the pop sound when an object is placed
            std::function<void(events::object_placed_on_field &)> on_place = [&](events::object_placed_on_field &event) {
                m_sound_manager.play("pop");
            };
            eventbus.subscribe("sound_on_place", on_place);

            // Play the error sound when an object cannot be placed
            std::function<void(events::object_cannot_be_placed_on_field &)> error_place = [&](events::object_cannot_be_placed_on_field &event) {
                m_sound_manager.play("error");
            };
            eventbus.subscribe("sound_when_not_placed", error_place);
        }

        void main_map::draw(unsigned int time_elapsed) {
            if(m_model.world->get_current_level().is_game_over(time_elapsed)|| m_model.world->get_current_level().is_goal_reached()){
                m_controller->show();
            }
            else{
                // this needs to be done with update event bus
                m_controller->update();
                m_model.world->draw(m_texture_manager, time_elapsed);
            }
        }

        void main_map::after() {
            // can be done by the objects as well
            m_model.world->unload(m_texture_manager);

            // Unload the music
            m_music_manager.unload("game_bg_music");

            // Remove sound listeners
            auto &eventbus = engine::eventbus::eventbus::get_instance();
            eventbus.unsubscribe("sound_on_place");
            eventbus.unsubscribe("sound_when_not_placed");

            // Unload sounds
            m_sound_manager.unload("pop");
            m_sound_manager.unload("error");
        }

        void main_map::set_controller(controllers::main_map_controller &controller) {
            m_controller = &controller;
        }
    }
}
