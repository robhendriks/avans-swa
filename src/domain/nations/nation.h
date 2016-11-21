//
// Created by Mark on 21-11-2016.
//

#ifndef CITY_DEFENCE_BASENATION_H
#define CITY_DEFENCE_BASENATION_H

#include <string>
#include <vector>
#include <memory>


namespace domain {
    namespace nations {

        class enemy;
        class nation {
        public:
            nation(std::string _name, std::string _prefixname);


            void setavailableenemies(std::vector<std::shared_ptr<enemy>> _enemies);


            std::string getName();

            std::string getprefixname();

            std::vector<std::shared_ptr<enemy>> getavailableenemies();

            ~nation();

        private:
            std::string name;
            std::string prefixname;
            std::vector<std::shared_ptr<enemy>> enemies;

        };
    }
}

#endif //CITY_DEFENCE_BASENATION_H
