//
// Created by robbie on 5-11-2016.
//

#ifndef CITY_DEFENCE_SOUND_MANAGER_H
#define CITY_DEFENCE_SOUND_MANAGER_H

#include <string>
#include <map>
#include <SDL_mixer.h>

namespace engine {
    namespace audio {
        class sound_manager {
        public:
            bool load(std::string file, std::string id);
            void play(std::string id);
            void unload(std::string id);
            ~sound_manager();
        private:
            std::map<std::string, Mix_Chunk*> m_sounds;
        };
    }
}

#endif //CITY_DEFENCE_SOUND_MANAGER_H
