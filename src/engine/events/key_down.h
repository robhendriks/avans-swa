//
// Created by robbie on 28-10-2016.
//

#ifndef CITY_DEFENCE_KEY_DOWN_H
#define CITY_DEFENCE_KEY_DOWN_H

#include "../input/keycodes.h"

namespace engine {
    namespace events {
        class key_down {
        public:
            key_down(input::keycodes::keycode key);

            input::keycodes::keycode get_keycode() const;

        private:
            input::keycodes::keycode m_key;
        };
    }
}

#endif //CITY_DEFENCE_KEY_DOWN_H
