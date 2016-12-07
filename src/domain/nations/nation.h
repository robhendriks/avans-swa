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

        typedef std::shared_ptr<enemy> enemy_ptr;

        class nation {
        public:
            nation();

            nation(const std::string &id, const std::string &name, const std::string &prefix);

            ~nation() = default;

            std::string get_id() const;

            void set_id(const std::string &id);

            std::string get_name() const;

            void set_name(const std::string &name);

            std::string get_prefix() const;

            void set_prefix(const std::string &prefix);

            const std::vector<enemy_ptr> &get_enemies() const;

            void set_enemies(const std::vector<enemy_ptr> &enemies);

        private:
            std::string m_id;
            std::string m_name;
            std::string m_prefix;
            std::vector<enemy_ptr> m_enemies;
        };

    }
}

#endif //CITY_DEFENCE_BASENATION_H
