//
// Created by Bert on 7-12-2016.
//

#include <iostream>
#include "ai.h"
#include "../objects/road.h"
#include "../objects/building.h"
#include "../../nations/enemy.h"

namespace domain {
    namespace map {
        namespace ai {
            ai::ai() {
                m_unit = nullptr;
                m_map = nullptr;
                m_next_field = nullptr;
                m_last_field = nullptr;
                m_current_target = nullptr;
            }

            void ai::update(unsigned int elapsed_time) {
                // oke here is where the magic happens ladies.

                // step 1: check if we have a target atm and if we can attack at all
                if (static_cast<int>(elapsed_time) - static_cast<int>(m_last_attack_time) >
                    m_unit->get_attack_speed() &&
                    m_current_target != nullptr) {
                    // step 1.1 attack and unset if target is destroyed
                    // TODO this needs to change to target now we know its always building
                    // TODO right now problem is that field object has no hp but 'target' does
                    if (dynamic_cast<domain::map::objects::building *>(m_current_target)->reduce_hitpoints(
                            m_unit->get_damage()) == 0) {
                        m_current_target = nullptr;
                    }
                }

                // step 2 check if we already have a target or not in case we killed the target then try to find another
                if (m_current_target == nullptr) {
                    // step 2.1 check if there is a target
                    for (auto &field_with_range : m_map->get_fields_in_range(m_unit->get_range(),
                                                                             m_current_field.get())) {
                        // step 2.1.1 check if the target is a target for us and if it is then set it
                        if (m_is_target(field_with_range.field->get_object())) {
                            m_current_target = field_with_range.field->get_object();
                            break;
                        }
                    }
                }

                // step 3: check if its time to move
                if (m_current_target == nullptr &&
                    static_cast<int>(elapsed_time) - m_last_movement_time > m_unit->get_movement()) {
                    m_last_movement_time = elapsed_time;
                    // step 3.1 check if we are in transition
                    if (m_next_field != nullptr) {
                        // step 3.1.1 check if we arrived at the target location or we have to choose a new target
                        if (m_next_field->get_box() == m_unit->get_box()) {
                            // first last set the last field to the current because we reached our destination
                            m_last_field = m_current_field;
                            // same for this.
                            m_current_field = m_next_field;
                            // and set our next location to this
                            m_next_field = get_next_field();
                        } else {
                            // animation logic
                            // for now lets move it straight away to the next one XD (100% movement speed
                            m_unit->set_box(std::make_shared<engine::math::box2_t>(m_next_field->get_box()));
                            m_next_field = nullptr;
                        }
                    } else {
                        m_next_field = get_next_field();
                    }
                }
            }

            std::shared_ptr<field> ai::get_spawn_point() {
                if (m_map != nullptr) {
                    auto spawn_point = std::shared_ptr<field>();

                    auto fields = m_map->get_fields_with_objects();
                    for (auto &field : fields) {
                        //if I can dynamic cast it to road, it's a road and a valid spawn point
                        auto road = dynamic_cast<domain::map::objects::road *>(field.get()->get_object());
                        if (road != nullptr) {
                            spawn_point = field;
                            break;
                        }
                    }
                    return spawn_point;
                } else {
                    return nullptr;
                }
            }

            void ai::move(unsigned int elapsed_time) {
            }

            std::shared_ptr<field> ai::get_next_field() {
                if (m_current_field == nullptr)
                    return nullptr;
                else {
                    // not going backwards currently
                    std::shared_ptr<field> best_neighbour = nullptr;
                    for (auto &neighbour : m_current_field->get_neighbors()) {
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
                    return best_neighbour;
                }
            }

            bool ai::is_initialised() const {
                return m_map != nullptr && m_unit != nullptr;
            }

            void ai::set_map(std::shared_ptr<map> map) {
                m_map = map;
                m_current_field = get_spawn_point();
                m_next_field = nullptr;
                m_last_field = nullptr;

                // start pos if possible
                if (m_unit != nullptr)
                    m_unit->set_box(std::make_shared<engine::math::box2_t>(m_current_field->get_box()));
            }

            void ai::set_unit(std::shared_ptr<domain::nations::enemy> unit) {
                m_unit = unit;

                // start pos if possible
                if (m_map != nullptr)
                    m_unit->set_box(std::make_shared<engine::math::box2_t>(m_current_field->get_box()));
            }

            void ai::set_target(std::function<bool(domain::map::objects::field_object *)> target) {
                m_is_target = target;
            }
        }
    }
}
