//
// Created by robbie on 5-12-2016.
//

#include "engine_state_changed.h"

namespace engine {
    namespace events {

        engine_state_changed::engine_state_changed(state new_state, state old_state) : m_new_state(new_state),
            m_old_state(old_state) {

        }

        state engine_state_changed::get_new_state() const {
            return m_new_state;
        }

        state engine_state_changed::get_old_state() const {
            return m_old_state;
        }
    }
}
