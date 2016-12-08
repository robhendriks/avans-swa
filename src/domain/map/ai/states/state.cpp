//
// Created by te on 08-Dec-16.
//

#include "state.h"

namespace domain {
    namespace map {
        namespace ai {
            namespace states {

                void state::set_next_state(std::shared_ptr<state> next) {
                    m_next = next;
                }

                std::shared_ptr<state> state::get_next_state() {
                    return m_next;
                }
            }
        }
    }
}