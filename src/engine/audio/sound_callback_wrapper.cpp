//
// Created by robbie on 7-11-2016.
//

#include <SDL_mixer.h>
#include "sound_callback_wrapper.h"

namespace engine {
    namespace audio {

        std::vector<std::function<void(int)>> sound_callback_wrapper::m_callbacks = {};
        bool sound_callback_wrapper::m_initialized = false;

        void sound_callback_wrapper::add_callback(std::function<void(int)> callback) {
            init();

            m_callbacks.push_back(callback);
        }

        void sound_callback_wrapper::channel_finished(int channel) {
            for (auto &callback : m_callbacks) {
                callback(channel);
            }
        }

        void sound_callback_wrapper::init() {
            if (!m_initialized) {
                Mix_ChannelFinished(channel_finished);
                m_initialized = true;
            }
        }

        void sound_callback_wrapper::destruct() {
            if (m_initialized) {
                m_callbacks.clear();
                m_initialized = false;
            }
        }
    }
}
