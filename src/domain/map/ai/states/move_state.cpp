//
// Created by te on 08-Dec-16.
//

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
                    // first we can only move if its a drawable
                    auto result = dynamic_cast<domain::drawable::drawable_game_object*>(ai->get_unit().get());
                    if(result != nullptr){
                        // step 3: check if its time to move
                        if (static_cast<int>(elapsed_time) - m_last_movement_time > 1000) {
                            m_last_movement_time = elapsed_time;
                            // step 3.1 check if we are in transition
                            if (m_next_field != nullptr) {
                                // step 3.1.1 check if we arrived at the target location or we have to choose a new target
                                if (m_next_field->get_box() == result->get_box()) {
                                    // first last set the last field to the current because we reached our destination
                                    m_last_field = ai->get_current_field();
                                    // same for this
                                    ai->set_current_field(m_next_field);
                                    // and set our next location to this
                                    m_next_field = get_next_field(ai);

                                    // now that move is complete lets switch to searching for targets
                                    ai->set_state(get_next_state());
                                } else {
                                    // animation logic
                                    move(ai, elapsed_time);
                                    // for now lets move it straight away to the next one XD (100% movement speed
                                    result->set_box(std::make_shared<engine::math::box2_t>(m_next_field->get_box()));
                                    m_next_field = nullptr;
                                }
                            } else {
                                m_next_field = get_next_field(ai);
                            }
                        }
                    }
                    else{
                        ai->set_state(get_next_state());
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

                }
            }
        }
    }
}