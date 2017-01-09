//
// Created by Mark on 21-11-2016.
//

#include "wavegenerator.h"
#include "../../domain/map/objects/building.h"
#include <algorithm>
#include <random>
#include <iostream>

namespace services {
    namespace wave {
        wavegenerator::wavegenerator(domain::map::ai::ai &ai) : m_ai(ai) {
            m_ai.set_new_target_func([&](domain::map::field* origin, domain::map::ai::ai* ai1){
                domain::map::objects::building* target = nullptr;
                for (auto &field_with_range : ai1->get_map().
                        get_fields_in_range(ai1->get_unit().get_range(), origin)) {
                    target = dynamic_cast<domain::map::objects::building*>(field_with_range.field.get_object());
                    if (target != nullptr) {
                        break;
                    }
                }
                return target;
            });

            m_ai.set_animation_transition_func([&](std::string title, domain::map::ai::ai* ai1, engine::math::box2_t& difference_between_you_and_target){
                if(title == "attack"){
                    // set speed of animation
                    ai1->get_unit().set_transition(
                            static_cast<long>(ai1->get_unit().get_attack_speed() / ai1->get_unit().get_max_column()));

                    // set correct animation (in case its not set yet to avoid resetting it
                    auto current_row = ai1->get_unit().get_current_row();
                    // lets just go towards whats furthest away for simplicity horizontal or vertical?
                    if(std::abs(difference_between_you_and_target.min.y) > std::abs(difference_between_you_and_target.min.x)){
                        // guess its vertical
                        if(difference_between_you_and_target.min.y > 0){ // then to the bottom
                            if( current_row != 4){
                                ai1->get_unit().set_current_row(4);
                            }
                        }
                        else{ // to top
                            if( current_row != 7){
                                ai1->get_unit().set_current_row(7);
                            }
                        }
                    }
                    else{
                        // guess horizontal
                        if(difference_between_you_and_target.min.x > 0){ // to right
                            if( current_row != 6){
                                ai1->get_unit().set_current_row(6);
                            }
                        }
                        else{ // to left
                            if( current_row != 5){
                                ai1->get_unit().set_current_row(5);
                            }
                        }
                    }
                }
                else if(title == "next-field-set" || title == "move"){
                    // set speed of animation
                    ai1->get_unit().set_transition(
                            static_cast<long>(ai1->get_unit().get_movement() / ai1->get_unit().get_max_column()));
                    // set correct animation (in case its not set yet to avoid resetting it
                    auto current_row = ai1->get_unit().get_current_row();

                    if(difference_between_you_and_target.min.x > 0){ // to right
                        if( current_row != 2){
                            ai1->get_unit().set_current_row(2);
                        }
                    }
                    else if(difference_between_you_and_target.min.x < 0){ // to left
                        if( current_row != 1){
                            ai1->get_unit().set_current_row(1);
                        }
                    }
                    else if(difference_between_you_and_target.min.y < 0){ // to top
                        if( current_row != 3){
                            ai1->get_unit().set_current_row(3);
                        }
                    }
                    else{ // to bottom
                        if( current_row != 0){
                            ai1->get_unit().set_current_row(0);
                        }
                    }
                }
            });
        }

        std::vector<std::pair<int, domain::nations::enemy*>> wavegenerator::generateEnemies(int _time,
                                                                                                            int _oppertunity,
                                                                                                            domain::nations::nation &_nation,
                                                                                                            bool _spread,
                                                                                                            int capoppertunity,
                                                                                                            bool _noboss) {

            //Start by clearing boss/to strong enemies based on the parameters
            auto list = _nation.get_available_enemies();
            auto olist = _nation.get_available_enemies();
            auto q = remove_if(list.begin(), list.end(),
                               [_noboss](domain::nations::enemy *element) {
                                   return element->is_boss() && _noboss;
                               });
            list.erase(q, list.end());

            if (capoppertunity != 0) {
                auto r = remove_if(list.begin(), list.end(),
                                   [capoppertunity](domain::nations::enemy *element) {
                                       return element->get_oppertunity_cost() > capoppertunity;
                                   });
                list.erase(r, list.end());
            }

            //Checks if enemies can be spawned based on the given _oppertunity
            std::sort(list.begin(), list.end());
            _nation.set_available_enemies(list);

            if (_nation.get_available_enemies().size() == 0 ||
                    _nation.get_available_enemies()[0]->get_oppertunity_cost() > _oppertunity) {
                //Returns empty list in case no enemy is cheap enough
                return std::vector<std::pair<int, domain::nations::enemy*>>(0);
            }

            //Createas the actual list of the enemies
            double temp_oppertunity = _oppertunity;
            temp_oppertunity = _oppertunity + static_cast<double>(_oppertunity) *
                                              (1 / static_cast<double>(_nation.get_available_enemies().size()));
            std::vector<std::pair<int, domain::nations::enemy*>> enemies;
            for (unsigned int i = 0; i < _nation.get_available_enemies().size(); i++) {
                temp_oppertunity = temp_oppertunity / 2;
                int amount = temp_oppertunity / (_nation.get_available_enemies()[i]->get_oppertunity_cost());
                for (int j = 0; j < amount; j++) {
                    domain::nations::enemy copy_e = *_nation.get_available_enemies()[i];
                    domain::nations::enemy *e = new domain::nations::enemy(copy_e);

                    auto *clone = m_ai.clone();
                    e->set_ai(*clone);

                    //std::pair<int, domain::nations::enemy*> test{0, e};
                    enemies.push_back(std::make_pair(0, e));
                }
            }

            //Creates timestamps for spawning
            //Create a templist with numbers
            int spreadedTime = _time / enemies.size();
            std::vector<int> templist(enemies.size());
            for (unsigned int i = 0; i < templist.size(); i++) {
                if (!_spread) {
                    enemies[i].first = i * spreadedTime;
                } else {
                    // TODO: uneven spread
                    if (olist.size() < (unsigned int) 100) {

                    }
                }
            }
            return enemies;
        }

        wavegenerator::~wavegenerator() {

        }

        domain::map::ai::ai &wavegenerator::get_ai() {
            return m_ai;
        }
    }
}
