//
// Created by robbie on 6-11-2016.
//

#ifndef CITY_DEFENCE_PLAY_SOUND_WHEN_OBJECT_CANNOT_BE_PLACED_ON_FIELD_H
#define CITY_DEFENCE_PLAY_SOUND_WHEN_OBJECT_CANNOT_BE_PLACED_ON_FIELD_H

#include <string>
#include "../engine/audio/sound_manager.h"
#include "../engine/eventbus/subscriber.h"
#include "../events/object_cannot_be_placed_on_field.h"

namespace listeners {
    class play_sound_when_object_cannot_be_placed_on_field : public engine::eventbus::subscriber<events::object_cannot_be_placed_on_field> {
    public:
        play_sound_when_object_cannot_be_placed_on_field(engine::audio::sound_manager &sound_manager, std::string sound_file);
        ~play_sound_when_object_cannot_be_placed_on_field();
        void on_event(events::object_cannot_be_placed_on_field &event);
    private:
        engine::audio::sound_manager &m_sound_manager;
    };

}

#endif //CITY_DEFENCE_PLAY_SOUND_WHEN_OBJECT_CANNOT_BE_PLACED_ON_FIELD_H
