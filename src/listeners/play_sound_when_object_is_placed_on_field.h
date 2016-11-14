//
// Created by robbie on 6-11-2016.
//

#ifndef CITY_DEFENCE_PLAY_SOUND_WHEN_OBJECT_IS_PLACED_ON_FIELD_H
#define CITY_DEFENCE_PLAY_SOUND_WHEN_OBJECT_IS_PLACED_ON_FIELD_H


#include "../engine/eventbus/subscriber.h"
#include "../events/object_placed_on_field.h"
#include "../engine/audio/sound_manager.h"
#include "../engine/audio/music_manager.h"

namespace listeners {
    class play_sound_when_object_is_placed_on_field
        : public engine::eventbus::subscriber<events::object_placed_on_field> {
    public:
        play_sound_when_object_is_placed_on_field(engine::audio::sound_manager &sound_manager,
                                                  engine::audio::music_manager &music_manager, std::string sound_file);

        ~play_sound_when_object_is_placed_on_field();

        void on_event(events::object_placed_on_field &event);

    private:
        engine::audio::sound_manager &m_sound_manager;
        engine::audio::music_manager &m_music_manager;
    };
}


#endif //CITY_DEFENCE_PLAY_SOUND_WHEN_OBJECT_IS_PLACED_ON_FIELD_H
