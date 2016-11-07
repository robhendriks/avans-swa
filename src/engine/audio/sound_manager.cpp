//
// Created by robbie on 5-11-2016.
//

#include "sound_manager.h"
#include "sound_callback_wrapper.h"

namespace engine {
    namespace audio {

        sound_manager::sound_manager() {
            m_playing_sounds = new std::map<int, std::tuple<std::string, sound::state, std::stack<int>>>();
            sound_callback_wrapper::add_callback([&](int channel) {
                sound_finished(channel);
            });
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

        bool sound_manager::load_if(std::string file, std::string id) {
            if (!is_loaded(id)) {
                return load(file, id);
            }

            return true;
        }

        bool sound_manager::is_loaded(std::string id) {
            return m_sounds.find(id) != m_sounds.end();
        }

        void sound_manager::sound_finished(int channel) {
            if (m_when_finished.find(channel) != m_when_finished.end()) {
                // Call callback
                m_when_finished[channel]();
                m_when_finished.erase(channel);
            }

            // Remove from playing sounds
            m_playing_sounds->erase(channel);
        }

        int sound_manager::play(std::string id, std::function<void()> when_finished, int volume, int fade_in, int loops) {
            if (is_loaded(id)) {
                Mix_VolumeChunk(m_sounds[id], volume);
                int channel;
                if (fade_in < 0) {
                    channel = Mix_PlayChannel(-1, m_sounds[id], loops);
                } else {
                    channel = Mix_FadeInChannel(-1, m_sounds[id], loops, fade_in);
                }

                if (channel != -1 ){
                    // Add to playing sounds
                    (*m_playing_sounds)[channel] = std::make_tuple(id, sound::PLAYING, std::stack<int>());

                    if (when_finished != NULL) {
                        m_when_finished[channel] = when_finished;
                    }

                    return channel;
                }
            }

            return -1;
        }

        int sound_manager::play_if(std::string id, bool count_paused, std::function<void()> when_finished, int volume, int fade_in,
                                   int loops) {
            auto channels = get_channels(id, count_paused);
            if (channels.size() == 0) {
                return play(id, when_finished, volume, fade_in, loops);
            }

            return channels[0];
        }

        std::vector<int> sound_manager::get_channels(std::string id, bool count_paused) const {
            std::vector<int> channels;
            for (auto &playing_sound : *m_playing_sounds) {
                auto tuple = playing_sound.second;
                if (std::get<0>(tuple) == id && (count_paused || std::get<1>(tuple) == sound::PLAYING)) {
                    channels.push_back(playing_sound.first);
                }
            }

            return channels;
        }

        void sound_manager::set_volume(int channel, int volume) {
            auto stack = get_volume_stack(channel);
            if (stack) {
                Mix_Volume(channel, volume);
                stack->push(volume);
            }
        }

        void sound_manager::set_volume_all(int volume) {
            for (auto &playing_sound : *m_playing_sounds) {
                set_volume(playing_sound.first, volume);
            }
        }

        int sound_manager::get_volume(int channel) const {
            auto stack = get_volume_stack(channel);
            if (stack) {
                stack->top();
            }

            return -1;
        }

        void sound_manager::pop_volume(int channel) {
            auto stack = get_volume_stack(channel);
            if (stack) {
                // Remove the top/current volume
                stack->pop();
                // Set the volume to the previous volume
                set_volume(channel, stack->top());
                // Pop again because set_volume will push again
                stack->pop();
            }
        }

        std::stack<int> *sound_manager::get_volume_stack(int channel) const {
            if (m_playing_sounds->find(channel) != m_playing_sounds->find(channel)) {
                auto sound = m_playing_sounds->at(channel);
                return &std::get<2>(sound);
            }

            return nullptr;
        }

        void sound_manager::pause(int channel) {
            if (m_playing_sounds->find(channel) != m_playing_sounds->end()) {
                auto &sound = m_playing_sounds->at(channel);
                if (std::get<1>(sound) == sound::PLAYING) {
                    Mix_Pause(channel);
                    std::get<1>(sound) = sound::PAUSED;
                }
            }
        }

        void sound_manager::pause_all() {
            for (auto &playing_sound : *m_playing_sounds) {
                pause(playing_sound.first);
            }
        }

        void sound_manager::resume(int channel) {
            if (m_playing_sounds->find(channel) != m_playing_sounds->end()) {
                auto &sound = m_playing_sounds->at(channel);
                if (std::get<1>(sound) == sound::PAUSED) {
                    Mix_Resume(channel);
                    std::get<1>(sound) = sound::PLAYING;
                }
            }
        }

        void sound_manager::resume_all() {
            for (auto &playing_sound : *m_playing_sounds) {
                resume(playing_sound.first);
            }
        }

        void sound_manager::stop(int channel, int fade_out) {
            if (m_playing_sounds->find(channel) != m_playing_sounds->end()) {
                if (fade_out == -1) {
                    Mix_HaltChannel(channel);
                } else {
                    Mix_FadeOutChannel(channel, fade_out);
                }

                // Don't wait for the callback, delete immediately
                m_playing_sounds->erase(channel);
            }
        }

        void sound_manager::stop_all(int fade_out) {
            for (auto it = m_playing_sounds->begin(); it != m_playing_sounds->end();) {
                stop(it->first, fade_out);
                // Set the iterator to begin because the stop method will delete the current element
                it = m_playing_sounds->begin();
            }
        }

        void sound_manager::unload(std::string id) {
            if (is_loaded(id)) {
                Mix_FreeChunk(m_sounds[id]);
                m_sounds.erase(id);
            }
        }

        std::map<int, std::tuple<std::string, sound::state, std::stack<int>>> *sound_manager::get_playing_sounds() const {
            return m_playing_sounds;
        }

        sound_manager::~sound_manager() {
            // Unload all sounds, iterator loop because the m_sounds will be changed inside
            for (auto it = m_sounds.begin(); it != m_sounds.end();) {
                unload(it->first);
                it = m_sounds.begin();
            }

            delete m_playing_sounds;
        }
    }
}
