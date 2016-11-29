//
// Created by robbie on 18-11-2016.
//

#include "display_changed.h"

namespace engine {
    namespace events {

        display_changed::display_changed(math::box2_t box) : m_box(box) {

        }

        math::box2_t display_changed::get_display_box() const {
            return m_box;
        }
    }
}
