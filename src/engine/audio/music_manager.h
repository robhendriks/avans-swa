//
// Created by robbie on 6-11-2016.
//

#ifndef CITY_DEFENCE_MUSIC_MANAGER_H
#define CITY_DEFENCE_MUSIC_MANAGER_H

#include <string>
#include <map>
#include <SDL_mixer.h>
#include <functional>
#include <stack>
#include "state.h"

namespace engine {
    namespace audio {
        class music_manager {
        public:
            bool load(std::string file, std::string id);
            bool load_if(std::string file, std::string id);
            bool is_loaded(std::string id);
            void unload(std::string id);
            void play(std::string id, std::function<void()> when_finished = NULL, int volume = 128, int fade_in = -1, int loops = -1);

            static void stop(int fade_out = -1);
            static void pause();
            static void resume();
            static void set_volume(int volume);
            static int get_volume();
            static void pop_volume();
            static std::stack<int> &get_volume_stack();
            static music::state get_state(std::string id = "");
            static std::string get_current_playing_id();
            ~music_manager();
        private:
            static void music_finished();

            std::map<std::string, Mix_Music*> m_songs;

            static std::stack<int> m_volume_stack;
            static std::string m_current_song;
            static music::state m_current_state;
            static std::function<void()> when_finished;
        };
    }
}

#endif //CITY_DEFENCE_MUSIC_MANAGER_H
