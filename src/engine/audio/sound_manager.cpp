//
// Created by robbie on 5-11-2016.
//

#include "sound_manager.h"

namespace engine {
    namespace audio {

        std::map<int, std::function<void()>> sound_manager::when_finished;

        sound_manager::sound_manager() {
            Mix_ChannelFinished(sound_finished);
        }

        bool sound_manager::load(std::string file, std::string id) {
            // Try to load the wav sound file
            Mix_Chunk *sound = Mix_LoadWAV(file.c_str());
            if (sound == nullptr) {
                // Couldn't load
                return false;
            }

            m_sounds[id] = sound;

            return true;
        }

        void sound_manager::sound_finished(int channel) {
            if (when_finished.find(channel) != when_finished.end()) {
                // Call callback
                sound_manager::when_finished[channel]();
                sound_manager::when_finished.erase(channel);
            }
        }

        void sound_manager::play(std::string id, std::function<void()> when_finished, int volume, int loops) {
            if (m_sounds.find(id) != m_sounds.end()) {
                Mix_VolumeChunk(m_sounds[id], volume);
                int channel = Mix_PlayChannel(-1, m_sounds[id], loops);
                if (when_finished != NULL) {
                    sound_manager::when_finished[channel] = when_finished;
                }
            }
        }

        void sound_manager::unload(std::string id) {
            if (m_sounds.find(id) != m_sounds.end()) {
                Mix_FreeChunk(m_sounds[id]);
                m_sounds.erase(id);
            }
        }

        sound_manager::~sound_manager() {
            // Unload all sounds, iterator loop because the m_sounds will be changed inside
            for (auto it = m_sounds.begin(); it != m_sounds.end();) {
                unload(it->first);
                it = m_sounds.begin();
            }
        }
    }
}
