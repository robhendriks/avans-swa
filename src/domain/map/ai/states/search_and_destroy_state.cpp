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
                    // if the last time we attacked was 500 ms ago then don't saturate the building anymore
                    if(m_current_target != nullptr && static_cast<int>(elapsed_time) - m_last_attack_time > 200){
                        m_current_target->set_saturated(false);
                    }

                    // step 1: check if we have a target atm and if we can attack at all
                    if (static_cast<int>(elapsed_time) - m_last_attack_time >
                        (1000/ai->get_unit()->get_attack_speed()) &&
                        m_current_target != nullptr) {
                        if(m_current_target->get_hp() <= 0){
                            m_current_target->set_saturated(false);
                            m_current_target = nullptr;
                        }
                        else{
                            m_last_attack_time = elapsed_time;
                            // step 1.1 attack and unset if target is destroyed
                            SDL_Log("%s %d", "hp before   : ", m_current_target->get_hp());
                            SDL_Log("%s %d", "elapsed time: ", elapsed_time);
                            m_current_target->set_saturated(true);
                            set_correct_animation(ai);
                            auto current_hp = m_current_target->lower_hitpoints(
                                    ai->get_unit()->get_damage());
                            SDL_Log("%s %d", "hp after   : ",current_hp);
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


                void search_and_destroy_state::set_correct_animation(domain::map::ai::ai *ai) {
                    // set speed of animation
                    ai->get_unit()->set_transition(
                            static_cast<long>(ai->get_unit()->get_attack_speed() / ai->get_unit()->get_max_column()));

                    // calculate difference between current location and the target
                    auto difference = calculate_difference_between_target_and_unit(ai);

                    // set correct animation (in case its not set yet to avoid resetting it
                    auto current_row = ai->get_unit()->get_current_row();
                    // lets just go towards whats furthest away for simplicity horizontal or vertical?
                    if(std::abs(difference.min.y) > std::abs(difference.min.x)){
                        // guess its vertical
                        if(difference.min.y > 0){ // then to the bottom
                            if( current_row != 4){
                                ai->get_unit()->set_current_row(4);
                            }
                        }
                        else{ // to top
                            if( current_row != 7){
                                ai->get_unit()->set_current_row(7);
                            }
                        }
                    }
                    else{
                        // guess horizontal
                        if(difference.min.x > 0){ // to right
                            if( current_row != 6){
                                ai->get_unit()->set_current_row(6);
                            }
                        }
                        else{ // to left
                            if( current_row != 5){
                                ai->get_unit()->set_current_row(5);
                            }
                        }
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