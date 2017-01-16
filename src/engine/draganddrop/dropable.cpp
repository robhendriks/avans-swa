//
// Created by robbie on 18-11-2016.
//

#include "dropable.h"

namespace engine {
    namespace draganddrop {

        void dropable::set_drag_and_drop(drag_and_drop *drag_and_drop1) {
            m_drag_and_drop = drag_and_drop1;
        }

        dropable::dropable() {

        }

        dropable::dropable(const dropable &other) {
            m_drag_and_drop = other.m_drag_and_drop;
        }
    }
}
