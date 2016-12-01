//
// Created by robbie on 1-12-2016.
//

#include "key_down.h"

namespace engine {
    namespace events {

        key_down::key_down(input::keycodes::keycode key) : m_key(key) {

        }

        input::keycodes::keycode key_down::get_keycode() const {
            return m_key;
        }
    }
}
