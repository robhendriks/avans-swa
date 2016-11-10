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

        /**
         * Load a file in the sound manager
         *
         * @param file
         * @param id
         * @return bool - whether it's loaded successfully or not
         */
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

        /**
         * Load a file in the sound manager if it's not already loaded
         *
         * @param file
         * @param id
         * @return bool - whether it's loaded successfully or not
         */
        bool sound_manager::load_if(std::string file, std::string id) {
            if (!is_loaded(id)) {
                return load(file, id);
            }

            return true;
        }

        /**
         * Check if an id is loaded in the manager
         *
         * @param id
         * @return bool - whether it's loaded or not
         */
        bool sound_manager::is_loaded(std::string id) {
            return m_sounds.find(id) != m_sounds.end();
        }

        /**
         * Called whenever a sound is finished/stops
         *
         * @param channel
         */
        void sound_manager::sound_finished(int channel) {
            if (m_when_finished.find(channel) != m_when_finished.end()) {
                // Call callback
                m_when_finished[channel]();
                m_when_finished.erase(channel);
            }

            // Remove from playing sounds
            m_playing_sounds->erase(channel);
        }

        /**
         * Start playing a sound
         *
         * @param id - id of the sound to play, the id should be loaded.
         * @param when_finished - callback that will be called when the sound is finished/stops
         * @param volume - the volume of the sound: max = 128
         * @param fade_in - fade in time in milliseconds, use -1 for no fade in
         * @param loops - the number of loops for the sound, use -1 for a infinite number of loops
         * @return int - the channel where the sound is being played
         */
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

        /**
         * Start playing a sound if the sound is not already being played
         *
         * @param id - id of the sound to play, the id should be loaded.
         * @param when_finished - callback that will be called when the sound is finished/stops
         * @param volume - the volume of the sound: max = 128
         * @param fade_in - fade in time in milliseconds, use -1 for no fade in
         * @param loops - the number of loops for the sound, use -1 for a infinite number of loops
         * @return int - the channel where the sound is being played, if there are multiple channels where the sound
         * is being played the first channel will be returned
         */
        int sound_manager::play_if(std::string id, bool count_paused, std::function<void()> when_finished, int volume, int fade_in,
                                   int loops) {
            auto channels = get_channels(id, count_paused);
            if (channels.size() == 0) {
                return play(id, when_finished, volume, fade_in, loops);
            }

            return channels[0];
        }

        /**
         * Get the playing channels for the id
         *
         * @param id
         * @param count_paused - whether paused sounds also should be returned
         * @return std::vector<int>
         */
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

        /**
         * Set the volume for a channel
         *
         * @param channel
         * @param volume - max 128
         */
        void sound_manager::set_volume(int channel, int volume) {
            auto stack = get_volume_stack(channel);
            if (stack) {
                Mix_Volume(channel, volume);
                stack->push(volume);
            }
        }

        /**
         * Set the volume for all the channels/playing sounds
         *
         * @param volume - max 128
         */
        void sound_manager::set_volume_all(int volume) {
            for (auto &playing_sound : *m_playing_sounds) {
                set_volume(playing_sound.first, volume);
            }
        }

        /**
         * Get the volume for a channel
         *
         * @param channel
         * @return int - the volume (0 - 128) or -1 when there is nothing played on the channel
         */
        int sound_manager::get_volume(int channel) const {
            auto stack = get_volume_stack(channel);
            if (stack) {
                stack->top();
            }

            return -1;
        }

        /**
         * Go back to the previous volume for the channel on the stack. If the stack size is less than 2,
         * nothing will happen.
         *
         * @param channel
         */
        void sound_manager::pop_volume(int channel) {
            auto stack = get_volume_stack(channel);
            if (stack && stack->size() > 1) {
                // Remove the top/current volume
                stack->pop();
                // Set the volume to the previous volume
                set_volume(channel, stack->top());
                // Pop again because set_volume will push again
                stack->pop();
            }
        }

        /**
         * Get the volume stack for the channel
         *
         * @param channel
         * @return *std::stack<int> - the volumes that are used for the channel. If there is nothing played on the
         * channel a nullptr will be returned.
         */
        std::stack<int> *sound_manager::get_volume_stack(int channel) const {
            if (m_playing_sounds->find(channel) != m_playing_sounds->find(channel)) {
                auto sound = m_playing_sounds->at(channel);
                return &std::get<2>(sound);
            }

            return nullptr;
        }

        /**
         * Pause the sound on the given channel, will only do something when there is a sound playing on the channel
         *
         * @param channel
         */
        void sound_manager::pause(int channel) {
            if (m_playing_sounds->find(channel) != m_playing_sounds->end()) {
                auto &sound = m_playing_sounds->at(channel);
                if (std::get<1>(sound) == sound::PLAYING) {
                    Mix_Pause(channel);
                    std::get<1>(sound) = sound::PAUSED;
                }
            }
        }

        /**
         * Pause all channels/playing sounds with the given sound id
         *
         * @param id
         */
        void sound_manager::pause_all(std::string id) {
            for (int channel : get_channels(id)) {
                pause(channel);
            }
        }

        /**
         * Pause all channels/playing sounds
         */
        void sound_manager::pause_all() {
            for (auto &playing_sound : *m_playing_sounds) {
                pause(playing_sound.first);
            }
        }

        /**
         * Resume the sound ont the given channel, will only do something when there is a paused sound on the channel
         * @param channel
         */
        void sound_manager::resume(int channel) {
            if (m_playing_sounds->find(channel) != m_playing_sounds->end()) {
                auto &sound = m_playing_sounds->at(channel);
                if (std::get<1>(sound) == sound::PAUSED) {
                    Mix_Resume(channel);
                    std::get<1>(sound) = sound::PLAYING;
                }
            }
        }

        /**
         * Resume all channels/playing sounds with the given sound id
         *
         * @param id
         */
        void sound_manager::resume_all(std::string id) {
            for (int channel : get_channels(id)) {
                resume(channel);
            }
        }

        /**
         * Resume all the paused channels/playing sounds
         */
        void sound_manager::resume_all() {
            for (auto &playing_sound : *m_playing_sounds) {
                resume(playing_sound.first);
            }
        }

        /**
         * Stop the sound on a channel
         *
         * @param channel
         * @param fade_out - fade out time in milliseconds, use -1 for no fade out
         */
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

        /**
         * Stop all channels/playing sounds with the given sound id
         *
         * @param id
         * @param fade_out - fade out time in milliseconds, use -1 for no fade out
         */
        void sound_manager::stop_all(std::string id, int fade_out) {
            for (int channel : get_channels(id)) {
                stop(channel);
            }
        }

        /**
         * Stop all channels/playing sounds
         *
         * @param fade_out - fade out time in milliseconds, use -1 for no fade out
         */
        void sound_manager::stop_all(int fade_out) {
            for (auto it = m_playing_sounds->begin(); it != m_playing_sounds->end();) {
                stop(it->first, fade_out);
                // Set the iterator to begin because the stop method will delete the current element
                it = m_playing_sounds->begin();
            }
        }

        /**
         * Unload the id in the manager. It's safe to call, also when the id is not loaded in the manager.
         * All the playing sounds with the given id are forced to stop
         *
         * @param id
         */
        void sound_manager::unload(std::string id) {
            if (is_loaded(id)) {
                Mix_FreeChunk(m_sounds[id]);
                m_sounds.erase(id);
            }
        }

        /**
         * Get the currently playing sounds
         *
         * @return *std::map<int, std::tuple<std::string, sound::state, std::stack<int>>>
         *  int = channel
         *  std::string = sound id
         *  sound::state = PLAYING OR PAUSED
         *  std::stack<int> = volume stack
         */
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
