//
// Created by te on 08-Dec-16.
//

#include "search_and_destroy_state.h"
#include "../ai.h"
#include "../../objects/building.h"
#include "../../../nations/enemy.h"
#include <cmath>

namespace domain {
    namespace map {
        namespace ai {
            namespace states {
                search_and_destroy_state::search_and_destroy_state() : m_current_target(nullptr) { }



                void search_and_destroy_state::update(ai *ai, unsigned int elapsed_time) {
                    // in case no target function is not defined go to next state
                    if(ai->get_new_target_func() == NULL){
                        ai->set_state(this->get_next_state());
                        return;
                    }

                    // if the last time we attacked was 2000 ms ago then don't saturate the building anymore
                    if(m_current_target != nullptr && static_cast<int>(elapsed_time) - m_last_attack_time > 2000){
                        m_current_target->set_saturated(false);
                    }

                    // step 1: check if we have a target atm and if we can attack at all
                    if (static_cast<int>(elapsed_time) - m_last_attack_time >
                        (ai->get_unit()->get_attack_speed()) &&
                        m_current_target != nullptr) {
                        if(m_current_target->get_hp() <= 0){
                            m_current_target->set_saturated(false);
                            m_current_target = nullptr;
                            if(ai->get_animation_transition_func() != NULL){
                                engine::math::box2_t box = engine::math::box2_t{{0,0},{0,0}};
                                ai->get_animation_transition_func()("target-destroyed", ai, box);
                            }
                        }
                        else {
                            m_last_attack_time = elapsed_time;
                            // step 1.1 attack and unset if target is destroyed
                            SDL_Log("%s %d", "hp before   : ", m_current_target->get_hp());
                            SDL_Log("%s %d", "elapsed time: ", elapsed_time);
                            m_current_target->set_saturated(true);

                            if(ai->get_animation_transition_func() != NULL){
                                engine::math::box2_t box = calculate_difference_between_target_and_unit(ai);
                                ai->get_animation_transition_func()("attack", ai, box);
                            }

                            auto current_hp = m_current_target->lower_hitpoints(
                                    ai->get_unit()->get_damage());
                            SDL_Log("%s %d", "hp after   : ",current_hp);

                            if (current_hp <= 0) {
                                auto enemy = dynamic_cast<domain::nations::enemy*>(m_current_target);
                                if (enemy) {
                                    enemy->get_ai()->set_state(std::make_shared<dead_state>()); // Not sure about this yet
                                    enemy->dispose();
                                }
                            }
                        }
                    }

                    // step 2 check if we already have a target or not in case we killed the target then try to find another
                    if (m_current_target == nullptr) {
                        // step 2.1 check if there is a target and then add it to the target
                        m_current_target = ai->get_new_target_func()(ai->get_current_field().get(), ai);
                    }

                    // if there is no target and it can move go to next state
                    if(m_current_target == nullptr && ai->get_unit()->get_movement() != 0){
                        ai->set_state(this->get_next_state());
                    }
                }

                engine::math::box2_t search_and_destroy_state::calculate_difference_between_target_and_unit(domain::map::ai::ai *ai) {
                    auto f_box = m_current_target->get_box();
                    auto u_box = ai->get_unit()->get_box();

                    return engine::math::box2_t {
                            {static_cast<float>(static_cast<double>(f_box.min.x - u_box.min.x) / 100),
                                    static_cast<float>(static_cast<double>(f_box.min.y - u_box.min.y)  / 100)},
                            {static_cast<float>(static_cast<double>(f_box.max.x - u_box.max.x)  / 100),
                                    static_cast<float>(static_cast<double>(f_box.max.y - u_box.max.y) / 100)}
                    };
                }
            }
        }
    }
}
