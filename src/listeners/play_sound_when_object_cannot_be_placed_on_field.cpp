//
// Created by robbie on 6-11-2016.
//

#include "play_sound_when_object_cannot_be_placed_on_field.h"

namespace listeners {

    play_sound_when_object_cannot_be_placed_on_field::play_sound_when_object_cannot_be_placed_on_field(
        engine::audio::sound_manager &sound_manager, std::string sound_file) : m_sound_manager(sound_manager) {

        m_sound_manager.load(sound_file, "not_placed");
    }

    play_sound_when_object_cannot_be_placed_on_field::~play_sound_when_object_cannot_be_placed_on_field() {
        m_sound_manager.unload("not_placed");
    }

    void play_sound_when_object_cannot_be_placed_on_field::on_event(events::object_cannot_be_placed_on_field &event) {
        m_sound_manager.play("not_placed");
    }
}
