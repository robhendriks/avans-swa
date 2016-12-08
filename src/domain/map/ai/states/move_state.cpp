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

                move_state::move_state() {
                    m_next_field = nullptr;
                    m_last_field = nullptr;
                }

                void move_state::update(domain::map::ai::ai *ai, unsigned int elapsed_time) {
                    // step 3.1 check if we are in transition
                    if (m_next_field != nullptr) {
                        // step 3.1.1 check if we arrived at the target location or we have to choose a new target
                        if (m_next_field->get_box() == ai->get_unit()->get_box()) {
                            // first last set the last field to the current because we reached our destination
                            m_last_field = ai->get_current_field();
                            // same for this
                            ai->set_current_field(m_next_field);
                            // now that we have moved set the current time we are on that field equal to the elapsed time.
                            m_time_moved_on_current_field = elapsed_time;
                            // and set our next location to this
                            m_next_field = get_next_field(ai);

                            // now that move is complete lets switch to searching for targets
                            ai->set_state(get_next_state());
                        } else {
                            // animation logic
                            move(ai, elapsed_time);
                            m_next_field = nullptr;
                        }
                    } else {
                        m_next_field = get_next_field(ai);
                    }
                }


                std::shared_ptr<field> move_state::get_next_field(domain::map::ai::ai *ai) {
                    if (ai->get_current_field() == nullptr)
                        return nullptr;
                    else {
                        // not going backwards currently
                        std::shared_ptr<field> best_neighbour = nullptr;
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
                    auto percentage = static_cast<double>(current_time_on_field) / static_cast<double>(ai->get_unit()->get_movement()) * 100;

                    // for easier use
                    auto f_box = m_next_field->get_box();
                    auto u_box = ai->get_unit()->get_box();

                    // differences and then 1%
                    auto difference_min_x_1 = static_cast<double>(f_box.min.x - u_box.min.x) / 100;
                    auto difference_min_y_1 = static_cast<double>(f_box.min.y - u_box.min.y)  / 100;
                    auto difference_max_x_1 = static_cast<double>(f_box.max.x - u_box.max.x)  / 100;
                    auto difference_max_y_1 = static_cast<double>(f_box.max.y - u_box.max.y) / 100;

                    // create a new box for the new location of the unit
                    engine::math::box2_t new_box = {
                        {static_cast<float>(u_box.min.x + (difference_min_x_1 * percentage)),
                                static_cast<float>(u_box.min.y + (difference_min_y_1 * percentage))},
                        {static_cast<float>(u_box.max.x + (difference_max_x_1 * percentage)),
                                static_cast<float>(u_box.max.y + (difference_max_y_1 * percentage))}
                    };

                    ai->get_unit()->set_box(std::make_shared<engine::math::box2_t>(new_box));

                }
            }
        }
    }
}