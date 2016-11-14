//
// Created by robbie on 7-11-2016.
//

#ifndef CITY_DEFENCE_SOUND_CALLBACK_WRAPPER_H
#define CITY_DEFENCE_SOUND_CALLBACK_WRAPPER_H


#include <functional>
#include <vector>

namespace engine {
    namespace audio {
        class sound_callback_wrapper {
        public:
            static void init();
            static void destruct();
            static void channel_finished(int channel);
            static void add_callback(std::function<void(int)> callback);
        private:
            static std::vector<std::function<void(int)>> m_callbacks;
            static bool m_initialized;
        };
    }
}


#endif //CITY_DEFENCE_SOUND_CALLBACK_WRAPPER_H
