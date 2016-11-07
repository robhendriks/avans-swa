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
            void play(std::string id, int volume = 128, int loops = -1);
            void set_volume(int volume);
            void stop();
            void pause();
            void resume();
            void unload(std::string id);
            int get_current_volume() const;
            int get_init_volume() const;
            music_state get_state(std::string id = "") const;
            std::string get_current_song() const;
            ~music_manager();
        private:
            std::map<std::string, Mix_Music*> m_songs;
            std::string m_current_song;
            music_state m_current_state;
            int m_volume;
            int m_init_volume;
        };
    }
}

#endif //CITY_DEFENCE_MUSIC_MANAGER_H
