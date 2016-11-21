//
// Created by Mark on 21-11-2016.
//

#include "wavegenerator.h"
#include <algorithm>
#include <random>

namespace services {

    wavegenerator::wavegenerator() {

    }


    std::vector<std::pair<int, std::shared_ptr<domain::nations::enemy>>> wavegenerator::generateEnemies(int _time,
                                                                                                        int _oppertunity,
                                                                                                        domain::nations::nation _nation,
                                                                                                        bool _spread,
                                                                                                        int capoppertunity,
                                                                                                        int _noboss) {

        std::sort(_nation.getavailableenemies().begin(), _nation.getavailableenemies().end());
        if (_nation.getavailableenemies().size() == 0 ||
            _nation.getavailableenemies()[0]->getOppertunity() > _oppertunity) {
            //Returns empty list
            return std::vector<std::pair<int, std::shared_ptr<domain::nations::enemy>>>(0);
        }
        //Optionally cuts away enemies above the capoppertunity and/or bosses.
        for(unsigned int i=0;i<_nation.getavailableenemies().size();i++){
            if(_nation.getavailableenemies()[i]->getBoss()==true &&_noboss==true){
                _nation.getavailableenemies().erase(_nation.getavailableenemies().begin() + i);
            }else if(_nation.getavailableenemies()[i]->getOppertunity() >capoppertunity && capoppertunity !=0){
                _nation.getavailableenemies().erase(_nation.getavailableenemies().begin() + i);
            }
        }


        //Createas a list of the enemies
        int temp_oppertunity = _oppertunity;
        _oppertunity = _oppertunity + (double) _oppertunity * (1 / (double) _nation.getavailableenemies().size());
        std::vector<std::pair<int, std::shared_ptr<domain::nations::enemy>>> enemies;
        for (unsigned int i =0;i< _nation.getavailableenemies().size();i++) {
            temp_oppertunity = temp_oppertunity / 2;
            int amount = temp_oppertunity/_nation.getavailableenemies()[i]->getOppertunity();
            for (int j = 0; j < amount; j++) {
                enemies.push_back(
                        std::pair<int, std::shared_ptr<domain::nations::enemy>>{0, _nation.getavailableenemies()[j]});
            }
        }


        //Creates timestamps for spawning
        //Create a templist with numbers
        int spreadedTime = _time*1000/enemies.size();
        std::vector<int> templist(enemies.size());
        for(unsigned int i=0;i<templist.size();i++){
            if(_spread ==false) {
                enemies[i].first = i * spreadedTime;
            }else{
           // TODO: uneven spread
            }

        }
        return enemies;




    }

    wavegenerator::~wavegenerator() {

    }


}