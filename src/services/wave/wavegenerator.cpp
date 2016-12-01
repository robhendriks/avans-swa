//
// Created by Mark on 21-11-2016.
//

#include "wavegenerator.h"
#include <algorithm>
#include <random>
#include <iostream>

namespace services {
    namespace wave {

        wavegenerator::wavegenerator() {

        }

        std::vector<std::pair<int, std::shared_ptr<domain::nations::enemy>>> wavegenerator::generateEnemies(int _time,
                                                                                                            int _oppertunity,
                                                                                                            domain::nations::nation _nation,
                                                                                                            bool _spread,
                                                                                                            int capoppertunity,
                                                                                                            bool _noboss) {
            //Start by clearing boss/to strong enemies based on the parameters
            auto list = _nation.getavailableenemies();
            auto olist = _nation.getavailableenemies();
            auto q = remove_if(list.begin(), list.end(),
                               [_noboss](std::shared_ptr<domain::nations::enemy> element) {
                                   return element->getBoss() == true&&_noboss==true;
                               });
            list.erase(q, list.end());

            if(capoppertunity!=0){
                auto r = remove_if(list.begin(), list.end(),
                                   [capoppertunity](std::shared_ptr<domain::nations::enemy> element) {
                                       return element->getOppertunity() >capoppertunity;
                                   });
                list.erase(r, list.end());
            }



            //Checks if enemies can be spawned based on the given _oppertunity
            std::sort(list.begin(), list.end());
            _nation.setavailableenemies(list);

            if (_nation.getavailableenemies().size() == 0 ||
                _nation.getavailableenemies()[0]->getOppertunity() > _oppertunity) {
                //Returns empty list in case no enemy is cheap enough
                return std::vector<std::pair<int, std::shared_ptr<domain::nations::enemy>>>(0);
            }



            //Createas the actual list of the enemies
            double temp_oppertunity = _oppertunity;
            temp_oppertunity = _oppertunity + static_cast<double>(_oppertunity) * (1 / static_cast<double>(_nation.getavailableenemies().size()));
            std::vector<std::pair<int, std::shared_ptr<domain::nations::enemy>>> enemies;
            for (unsigned int i = 0; i < _nation.getavailableenemies().size(); i++) {
                temp_oppertunity = temp_oppertunity / 2;
                int amount = temp_oppertunity /(_nation.getavailableenemies()[i]->getOppertunity());
                for (int j = 0; j < amount; j++) {
                    std::shared_ptr<domain::nations::enemy> e = std::make_shared<domain::nations::enemy>(*_nation.getavailableenemies()[i]);
                    enemies.push_back(

                            std::pair<int, std::shared_ptr<domain::nations::enemy>>{0,
                                                                                    e});

                }
            }


            //Creates timestamps for spawning
            //Create a templist with numbers
            int spreadedTime = _time/ enemies.size();
            std::vector<int> templist(enemies.size());
            for (unsigned int i = 0; i < templist.size(); i++) {
                if (_spread == false) {
                    enemies[i].first = i * spreadedTime;
                } else {
                    // TODO: uneven spread
                    if(olist.size()<(unsigned int)100){

                    }
                }

            }
            return enemies;


        }


        wavegenerator::~wavegenerator() {

        }

    }


}
