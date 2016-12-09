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
                    if (static_cast<int>(elapsed_time) - m_last_attack_time >
                        (1000/ai->get_unit()->get_attack_speed()) &&
                        m_current_target != nullptr) {
                        m_last_attack_time = elapsed_time;
                        // step 1.1 attack and unset if target is destroyed
                        // TODO this needs to change to target now we know its always building
                        // TODO right now problem is that field object has no hp but 'target' does
                        SDL_Log("%s %d", "hp before   : ", m_current_target->get_hp());
                        SDL_Log("%s %d", "elapsed time: ", elapsed_time);
                        auto current_hp = m_current_target->lower_hitpoints(
                                ai->get_unit()->get_damage());
                        SDL_Log("%s %d", "hp after   : ",current_hp);
                        if (current_hp <= 0) {
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