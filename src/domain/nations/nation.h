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
            nation(std::string _name, std::string _prefix_name);


            void setavailableenemies(std::vector<std::shared_ptr<enemy>> _enemies);


            std::string get_name();

            std::string get_prefix_name();

            std::vector<std::shared_ptr<enemy>> get_available_enemies();

            ~nation();

        private:
            std::string m_name;
            std::string m_prefix_name;
            std::vector<std::shared_ptr<enemy>> m_enemies;

        };
    }
}

#endif //CITY_DEFENCE_BASENATION_H
