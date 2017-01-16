//
// Created by robbie on 18-11-2016.
//

#include "dragable.h"

namespace engine {
    namespace draganddrop {
        void dragable::set_drag_and_drop(drag_and_drop *drag_and_drop1) {
            m_drag_and_drop = drag_and_drop1;
        }

        dragable::dragable(const dragable &other) {
            m_drag_and_drop = other.m_drag_and_drop;
        }

        dragable::dragable() {}
    }
}
