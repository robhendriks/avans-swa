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

                auto *move = new domain::map::ai::states::move_state();
                auto *attack = new domain::map::ai::states::search_and_destroy_state();

                m_state = state::SEARCH_AND_DESTROY;

                m_states[state::DEAD] = new states::dead_state();
                m_states[state::SEARCH_AND_DESTROY] = attack;
                m_states[state::MOVE] = move;
            }

            ai::~ai() {
                for (auto &state : m_states) {
                    delete state.second;
                }
            }

            void ai::update(unsigned int elapsed_time) {
                m_states[m_state]->update(this, elapsed_time);
            }

            field *ai::get_spawn_point() {
                if (m_map != nullptr) {
                    field *spawn_point = nullptr;

                    auto fields = m_map->get_fields_with_objects();
                    for (auto &field : fields) {
                        //if I can dynamic cast it to road, it's a road and a valid spawn point
                        auto road = dynamic_cast<domain::map::objects::road *>(field->get_object());
                        if (road != nullptr) {
                            spawn_point = field;
                            break;
                        }
                    }

                    return spawn_point;
                }

                return nullptr;
            }
            bool ai::is_initialised() const {
                return m_map != nullptr && m_unit != nullptr;
            }

            void ai::set_map(map &map1) {
                m_map = &map1;
                m_current_field = get_spawn_point();

                // start pos if possible
                if (m_unit != nullptr){
                    m_unit->set_box(m_current_field->get_box());
                }
            }

            void ai::set_unit(domain::combat::attacker &unit) {
                m_unit = &unit;

                // start pos if possible
                if (m_map != nullptr) {
                    m_unit->set_box(m_current_field->get_box());
                }
            }

            domain::combat::attacker &ai::get_unit() {
                return *m_unit;
            }

            void ai::set_new_target_func(std::function<domain::combat::defender* (domain::map::field* origin, domain::map::ai::ai* ai)>  target) {
                m_new_target_func = target;
            }

            std::function<domain::combat::defender* (domain::map::field* origin, domain::map::ai::ai* ai)>  ai::get_new_target_func() {
                return m_new_target_func;
            }

            std::function<void (std::string title, domain::map::ai::ai* ai, engine::math::box2_t& difference)>  ai::get_animation_transition_func(){
                return m_animation_transition_func;
            }

            void ai::set_animation_transition_func(std::function<void(std::string title, domain::map::ai::ai *ai, engine::math::box2_t& difference)> func) {
                m_animation_transition_func = func;
            }

            void ai::set_state(state state1) {
                m_state = state1;
            }

            map &ai::get_map() const {
                return *m_map;
            }

            field *ai::get_current_field() {
                return m_current_field;
            }

            void ai::set_current_field(field &field1) {
                m_current_field = &field1;
            }

            ai *ai::clone() {
                ai *result = new ai();
                result->set_unit(*m_unit);
                result->set_map(*m_map);
                result->set_new_target_func(m_new_target_func);
                result->set_animation_transition_func(m_animation_transition_func);
                return result;
            }

            state ai::get_current_state() const {
                return m_state;
            }
        }
    }
}
