//
// Created by robbie on 6-11-2016.
//

#include "play_sound_when_object_is_placed_on_field.h"

namespace listeners {

    play_sound_when_object_is_placed_on_field::play_sound_when_object_is_placed_on_field(
        engine::audio::sound_manager &sound_manager, engine::audio::music_manager &music_manager,
        std::string sound_file) : m_sound_manager(sound_manager), m_music_manager(music_manager) {
        m_sound_manager.load(sound_file, "pop");
    }

    play_sound_when_object_is_placed_on_field::~play_sound_when_object_is_placed_on_field() {
        m_sound_manager.unload("pop");
    }

    void play_sound_when_object_is_placed_on_field::on_event(events::object_placed_on_field &event) {
        if (m_music_manager.get_state() == engine::audio::music::state::PLAYING) {
            // Decrease bg music volume
            m_music_manager.set_volume(50);
            m_sound_manager.play("pop", [&]() {
                m_music_manager.pop_volume();
            });
        } else {
            // No bg music
            m_sound_manager.play("pop");
        }
    }
}
