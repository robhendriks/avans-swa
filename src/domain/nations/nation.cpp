//
// Created by Mark on 21-11-2016.
//

#include "nation.h"

namespace domain {
    namespace nations {
        nation::nation(std::string _name, std::string _prefixname) {
            name = _name;
            prefixname = _prefixname;
        }

        void nation::set_available_enemies(std::vector<std::shared_ptr<enemy>> _enemies) {
            enemies = _enemies;
        }


        std::string nation::getName() {
            return name;
        }

        std::string nation::getprefixname() {
            return prefixname;
        }

        std::vector<std::shared_ptr<enemy>> nation::getavailableenemies() {
            return enemies;
        }

        nation::~nation() {

        }

    }
}
