//
// Created by te on 08-Dec-16.
//

#include <iostream>
#include "move_state.h"
#include "../ai.h"
#include "../../objects/road.h"

namespace domain {
    namespace map {
        namespace ai {
            namespace states {

                move_state::move_state() : m_last_field(nullptr), m_next_field(nullptr){}

                void move_state::update(domain::map::ai::ai *ai, unsigned int elapsed_time) {
                    // in case the unit can never get to the location it wants to go to then move to next state
                    if(ai->get_unit().get_movement() == 0)
                        ai->set_state(SEARCH_AND_DESTROY);
                    else{
                        // step 3.1 check if we are in transition
                        if (m_next_field != nullptr) {
                            // step 3.1.1 check if we arrived at the target location or we have to choose a new target
                            if (m_next_field->get_box() == ai->get_unit().get_box()) {
                                // first last set the last field to the current because we reached our destination
                                m_last_field = ai->get_current_field();
                                // same for this
                                ai->set_current_field(*m_next_field);

                                ai->get_unit().set_current_field(*m_next_field);

                                // now that we have moved set the current time we are on that field equal to the elapsed time.
                                m_time_moved_on_current_field = elapsed_time;
                                // and set our next location to this
                                m_next_field = get_next_field(ai);

                                // next up calculate the movement we have to make
                                calculate_initial_state_with_difference(ai);

                                // next up set the animation based on the difference
                                if(ai->get_animation_transition_func() != NULL){
                                    ai->get_animation_transition_func()("next-field-set", ai, m_difference_box);
                                }
                                // now that move is complete lets switch to searching for targets
                                pauze(elapsed_time);
                                ai->set_state(SEARCH_AND_DESTROY);
                            } else {
                                // in case it was a pauze then we need to make it so we don't insta jump to the other field
                                // because elapsed time is invalid
                                recalculate_time(elapsed_time);

                                // move logic
                                move(ai, elapsed_time);

                                // animation logic
                                if(ai->get_animation_transition_func() != NULL){
                                    ai->get_animation_transition_func()("move", ai, m_difference_box);
                                }
                            }
                        } else {
                            m_next_field = get_next_field(ai);
                            calculate_initial_state_with_difference(ai);
                            // animation logic
                            if(ai->get_animation_transition_func() != NULL){
                                ai->get_animation_transition_func()("next-field-set", ai, m_difference_box);
                            }
                        }
                    }
                }

                field *move_state::get_next_field(domain::map::ai::ai *ai) {
                    if (ai->get_current_field() == nullptr)
                        return nullptr;
                    else {
                        // not going backwards currently
                        field *best_neighbour = nullptr;
                        for (auto &neighbour : ai->get_current_field()->get_neighbors()) {
                            // in case its the field we came from ignore it.
                            if (m_last_field == nullptr || m_last_field != neighbour) {
                                auto object = neighbour->get_object();

                                //check it's type is a road
                                auto r = dynamic_cast<domain::map::objects::road *>(object);
                                if (r != nullptr) {
                                    if (best_neighbour == nullptr ||
                                        best_neighbour->get_weight() <= neighbour->get_weight()) {
                                        best_neighbour = neighbour;
                                    }
                                }
                            }
                        }
                        return best_neighbour == nullptr ? m_last_field : best_neighbour;
                    }
                }

                void move_state::move(domain::map::ai::ai *ai, unsigned int elapsed_time) {
                    // then its the spawn point and we just set the time
                    if(m_time_moved_on_current_field == -1){
                        m_time_moved_on_current_field = elapsed_time;
                    }

                    // time on field
                    auto current_time_on_field = elapsed_time - m_time_moved_on_current_field;
                    // % of total time
                    double percentage = static_cast<double>(current_time_on_field) / static_cast<double>(ai->get_unit().get_movement()) * 100;

                    // if its called not on the precise time reset it to 100 to avoid issues like 102%
                    if(percentage > 100)
                        percentage = 100;

                    // create a new box for the new location of the unit
                    engine::math::box2_t new_box = {
                        {static_cast<float>(m_init_unit_box.min.x + (m_difference_box.min.x * percentage)),
                                static_cast<float>(m_init_unit_box.min.y + (m_difference_box.min.y * percentage))},
                        {static_cast<float>(m_init_unit_box.max.x + (m_difference_box.max.x * percentage)),
                                static_cast<float>(m_init_unit_box.max.y + (m_difference_box.max.y * percentage))}
                    };


                     ai->get_unit().set_box(new_box);
                }

                void move_state::calculate_initial_state_with_difference(domain::map::ai::ai *ai) {

                    auto f_box = m_next_field->get_box();
                    auto u_box = ai->get_unit().get_box();

                    m_init_unit_box = u_box;
                    m_difference_box = {
                            {static_cast<float>(static_cast<double>(f_box.min.x - u_box.min.x) / 100),
                                    static_cast<float>(static_cast<double>(f_box.min.y - u_box.min.y)  / 100)},
                            {static_cast<float>(static_cast<double>(f_box.max.x - u_box.max.x)  / 100),
                                    static_cast<float>(static_cast<double>(f_box.max.y - u_box.max.y) / 100)}
                    };
                }

                void move_state::recalculate_time(unsigned int time) {
                    if(m_pauzed){
                        auto time_on_field = m_pauzed_at - m_time_moved_on_current_field;
                        // reset it back to the same difference
                        m_time_moved_on_current_field = time - time_on_field;

                        // now its not pauzed anymore obviously
                        m_pauzed = false;
                    }
                }

                void move_state::pauze(unsigned int time) {
                    m_pauzed = true;
                    m_pauzed_at = time;
                }
            }
        }
    }
}
