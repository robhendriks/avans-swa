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

        using enemy_ptr = std::shared_ptr<enemy>;
        using enemy_ptr_vector = std::vector<enemy_ptr>;

        class nation {
        public:
            nation();

            nation (const std::string &id, const std::string &name, const std::string &prefix, const enemy_ptr_vector &enemies);

            nation(const std::string &id, const std::string &name, const std::string &prefix);

            ~nation() = default;

            std::string get_id() const;

            void set_id(const std::string &id);

            std::string get_name() const;

            void set_name(const std::string &name);

            std::string get_prefix() const;

            void set_prefix(const std::string &prefix);

            const enemy_ptr_vector &get_enemies() const;

            void set_enemies(const enemy_ptr_vector &enemies);

        private:
            std::string m_id;
            std::string m_name;
            std::string m_prefix;
            enemy_ptr_vector m_enemies;
        };

    }
}

#endif //CITY_DEFENCE_BASENATION_H
