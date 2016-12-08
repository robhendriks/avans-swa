//
// Created by te on 08-Dec-16.
//

#include "search_and_destroy_state.h"
#include "../ai.h"
#include "../../objects/building.h"
#include "../../../nations/enemy.h"

namespace domain {
    namespace map {
        namespace ai {
            namespace states {
                search_and_destroy_state::search_and_destroy_state() {
                    m_current_target = nullptr;
                }

                void search_and_destroy_state::update(ai *ai, unsigned int elapsed_time) {
                    // step 1: check if we have a target atm and if we can attack at all
                    if (static_cast<int>(elapsed_time) - static_cast<int>(m_last_attack_time) >
                        ai->get_unit()->get_attack_speed() &&
                        m_current_target != nullptr) {
                        // step 1.1 attack and unset if target is destroyed
                        // TODO this needs to change to target now we know its always building
                        // TODO right now problem is that field object has no hp but 'target' does
                        if (m_current_target->lower_hitpoints(
                                ai->get_unit()->get_damage()) <= 0) {
                            m_current_target = nullptr;
                        }
                    }

                    // step 2 check if we already have a target or not in case we killed the target then try to find another
                    if (m_current_target == nullptr) {
                        // step 2.1 check if there is a target and then add it to the target
                        m_current_target = ai->get_new_target_func()(ai->get_current_field().get(), ai);
                    }

                    // if there is no target then lets go to next state
                    if(m_current_target == nullptr)
                        ai->set_state(this->get_next_state());
                }
            }
        }
    }
}