//
// Created by robbie on 5-11-2016.
//

#ifndef CITY_DEFENCE_SOUND_MANAGER_H
#define CITY_DEFENCE_SOUND_MANAGER_H

#include <string>
#include <map>
#include <SDL_mixer.h>
#include <functional>

namespace engine {
    namespace audio {
        class sound_manager {
        public:
            sound_manager();
            bool load(std::string file, std::string id);
            void play(std::string id, std::function<void()> when_finished = NULL, int volume = 128, int loops = 0);
            void unload(std::string id);
            ~sound_manager();
        private:
            static void sound_finished(int channel);

            std::map<std::string, Mix_Chunk*> m_sounds;
            static std::function<void()> when_finished;
        };
    }
}

#endif //CITY_DEFENCE_SOUND_MANAGER_H
