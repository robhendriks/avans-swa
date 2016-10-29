//
// Created by robbie on 29-10-2016.
//

#include "window_cleared.h"

namespace engine {
    namespace events {

        window_cleared::window_cleared(float interpolation) : m_interpolation(interpolation) {
        }

        float window_cleared::get_interpolation() const {
            return m_interpolation;
        }
    }
}
