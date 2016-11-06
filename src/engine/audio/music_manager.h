//
// Created by robbie on 6-11-2016.
//

#ifndef CITY_DEFENCE_MUSIC_MANAGER_H
#define CITY_DEFENCE_MUSIC_MANAGER_H

#include <string>
#include <map>
#include <SDL_mixer.h>

namespace engine {
    namespace audio {
        enum music_state { PLAYING, PAUSED, LOADED, NOT_LOADED };

        class music_manager {
        public:
            music_manager();
            bool load(std::string file, std::string id);
            void play(std::string id);
            void stop();
            void pause();
            void resume();
            void unload(std::string id);
            music_state get_state(std::string id);
            ~music_manager();
        private:
            std::map<std::string, Mix_Music*> m_songs;
            std::string *m_current_song;
            music_state m_current_state;
        };
    }
}

#endif //CITY_DEFENCE_MUSIC_MANAGER_H
