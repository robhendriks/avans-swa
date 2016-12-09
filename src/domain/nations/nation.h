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
            nation(const std::string &id, const std::string &name, std::string &prefix);

            std::string get_id() const;

            std::string get_name() const;

            std::string get_prefix() const;

            std::vector<std::shared_ptr<enemy>> get_enemies() const;

            void set_enemies(const std::vector<std::shared_ptr<enemy>> &enemies);

            ~nation() = default;

        private:
            std::string m_id;
            std::string m_name;
            std::string m_prefix;
            std::vector<std::shared_ptr<enemy>> m_enemies;
        };
    }
}

#endif //CITY_DEFENCE_BASENATION_H
