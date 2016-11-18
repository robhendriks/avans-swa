//
// Created by robbie on 17-11-2016.
//

#include "mouse_motion.h"

namespace engine {
    namespace events {

        mouse_motion::mouse_motion(math::vec2_t mouse_position) : m_mouse_position(mouse_position) {

        }

        math::vec2_t mouse_motion::get_mouse_position() const {
            return m_mouse_position;
        }
    }
}
