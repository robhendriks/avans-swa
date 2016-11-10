//
// Created by robbie on 5-11-2016.
//

#ifndef CITY_DEFENCE_SOUND_MANAGER_H
#define CITY_DEFENCE_SOUND_MANAGER_H

#include <string>
#include <map>
#include <SDL_mixer.h>
#include <functional>
#include <stack>
#include <vector>
#include "state.h"

namespace engine {
    namespace audio {
        class sound_manager {
        public:
            sound_manager();
            bool load(std::string file, std::string id);
            bool load_if(std::string file, std::string id);
            bool is_loaded(std::string id);
            int play(std::string id, std::function<void()> when_finished = NULL, int volume = 128, int fade_in = -1, int loops = 0);
            int play_if(std::string id, bool count_paused = true, std::function<void()> when_finished = NULL, int volume = 128, int fade_in = -1, int loops = 0);
            std::vector<int> get_channels(std::string id, bool count_paused = true) const;
            void set_volume(int channel, int volume);
            void set_volume_all(int volume);
            int get_volume(int channel) const;
            void pop_volume(int channel);
            std::stack<int> *get_volume_stack(int channel) const;
            void pause(int channel);
            void pause_all(std::string id);
            void pause_all();
            void resume(int channel);
            void resume_all(std::string id);
            void resume_all();
            void stop(int channel, int fade_out = -1);
            void stop_all(std::string id, int fade_out = -1);
            void stop_all(int fade_out = -1);
            void unload(std::string id);
            std::map<int, std::tuple<std::string, sound::state, std::stack<int>*>> *get_playing_sounds() const;
            ~sound_manager();
        private:
            void sound_finished(int channel);
            void erase_playing_sound(int channel);

            std::map<int, std::tuple<std::string, sound::state, std::stack<int>*>> *m_playing_sounds;
            std::map<std::string, Mix_Chunk*> m_sounds;
            std::map<int, std::function<void()>> m_when_finished;
        };
    }
}

#endif //CITY_DEFENCE_SOUND_MANAGER_H
