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
        wavegenerator::wavegenerator(std::shared_ptr<domain::map::ai::ai> ai) {
            m_ai = ai;
            ai->set_target_func([](domain::map::objects::field_object *object) {
                return dynamic_cast<domain::map::objects::building *>(object) != nullptr;
            });
        }

        std::vector<std::pair<int, std::shared_ptr<domain::nations::enemy>>> wavegenerator::generateEnemies(int _time,
                                                                                                            int _oppertunity,
                                                                                                            domain::nations::nation _nation,
                                                                                                            bool _spread,
                                                                                                            int capoppertunity,
                                                                                                            bool _noboss) {
            //Start by clearing boss/to strong enemies based on the parameters
            auto list = _nation.get_available_enemies();
            auto olist = _nation.get_available_enemies();
            auto q = remove_if(list.begin(), list.end(),
                               [_noboss](std::shared_ptr<domain::nations::enemy> element) {
                                   return element->is_boss() == true && _noboss == true;
                               });
            list.erase(q, list.end());

            if (capoppertunity != 0) {
                auto r = remove_if(list.begin(), list.end(),
                                   [capoppertunity](std::shared_ptr<domain::nations::enemy> element) {
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
                return std::vector<std::pair<int, std::shared_ptr<domain::nations::enemy>>>(0);
            }



            //Createas the actual list of the enemies
            double temp_oppertunity = _oppertunity;
            temp_oppertunity = _oppertunity + static_cast<double>(_oppertunity) *
                                              (1 / static_cast<double>(_nation.get_available_enemies().size()));
            std::vector<std::pair<int, std::shared_ptr<domain::nations::enemy>>> enemies;
            for (unsigned int i = 0; i < _nation.get_available_enemies().size(); i++) {
                temp_oppertunity = temp_oppertunity / 2;
                int amount = temp_oppertunity / (_nation.get_available_enemies()[i]->get_oppertunity_cost());
                for (int j = 0; j < amount; j++) {
                    std::shared_ptr<domain::nations::enemy> e = std::make_shared<domain::nations::enemy>(
                            *_nation.get_available_enemies()[i]);

                    if (m_ai != nullptr) {
                        domain::map::ai::ai clone = m_ai->clone();
                        clone.set_unit(e);
                        e->set_ai(std::make_shared<domain::map::ai::ai>(clone));
                    }

                    enemies.push_back(

                            std::pair<int, std::shared_ptr<domain::nations::enemy>>{0, e});

                }
            }


            //Creates timestamps for spawning
            //Create a templist with numbers
            int spreadedTime = _time / enemies.size();
            std::vector<int> templist(enemies.size());
            for (unsigned int i = 0; i < templist.size(); i++) {
                if (_spread == false) {
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

        std::shared_ptr<domain::map::ai::ai> wavegenerator::get_ai() {
            return m_ai;
        }
    }


}
