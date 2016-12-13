//
// Created by Bert on 7-12-2016.
//

#include <iostream>
#include "ai.h"
#include "../objects/road.h"
#include "../objects/building.h"
#include "states/search_and_destroy_state.h"
#include "states/move_state.h"

namespace domain {
    namespace map {
        namespace ai {
            ai::ai() : m_current_field(nullptr), m_map(nullptr), m_unit(nullptr) {
                std::shared_ptr<domain::map::ai::states::move_state> move = std::make_shared<domain::map::ai::states::move_state>(domain::map::ai::states::move_state());
                std::shared_ptr<domain::map::ai::states::search_and_destroy_state> attack = std::make_shared<domain::map::ai::states::search_and_destroy_state>(domain::map::ai::states::search_and_destroy_state());
                move->set_next_state(attack);
                attack->set_next_state(move);
                m_state = move;
            }

            void ai::update(unsigned int elapsed_time) {
                // oke here is where the magic happens ladies.
                m_state->update(this, elapsed_time);
                // thats it aplause.
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
            bool ai::is_initialised() const {
                return m_map != nullptr && m_unit != nullptr;
            }

            void ai::set_map(std::shared_ptr<map> map) {
                m_map = map;
                m_current_field = get_spawn_point();

                // start pos if possible
                if (m_unit != nullptr){
                    m_unit->set_box(std::make_shared<engine::math::box2_t>(m_current_field->get_box()));
                }
            }

            void ai::set_unit(std::shared_ptr<domain::combat::attacker> unit) {
                m_unit = unit;

                // start pos if possible
                if (m_map != nullptr){
                    m_unit->set_box(std::make_shared<engine::math::box2_t>(m_current_field->get_box()));
                }
            }

            std::shared_ptr<domain::combat::attacker> ai::get_unit() {
                return m_unit;
            }

            void ai::set_new_target_func(std::function<domain::combat::defender* (domain::map::field* origin, domain::map::ai::ai* ai)>  target) {
                m_new_target_func = target;
            }

            std::function<domain::combat::defender* (domain::map::field* origin, domain::map::ai::ai* ai)>  ai::get_new_target_func() {
                return m_new_target_func;
            }

            void ai::set_state(std::shared_ptr<states::state> state) {
                m_state = state;
            }

            std::shared_ptr<map> ai::get_map() {
                return m_map;
            }

            std::shared_ptr<field> ai::get_current_field() {
                return m_current_field;
            }

            void ai::set_current_field(std::shared_ptr<field> field) {
                m_current_field = field;
            }

            ai ai::clone() {
                ai result = ai();
                result.set_unit(m_unit);
                result.set_map(m_map);
                result.set_new_target_func(m_new_target_func);
                return result;
            }

            std::shared_ptr<states::state> ai::get_state() const {
                return m_state;
            }
        }
    }
}
