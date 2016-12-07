//
// Created by Mark on 21-11-2016.
//

#include "nation.h"

namespace domain {
    namespace nations {

        nation::nation() {}

        nation::nation(const std::string &id, const std::string &name, const std::string &prefix)
            : m_id{id}, m_name{name}, m_prefix{prefix} {}

        std::string nation::get_id() const {
            return m_id;
        }

        void nation::set_id(const std::string &id) {
            m_id = id;
        }

        std::string nation::get_name() const {
            return m_name;
        }

        void nation::set_name(const std::string &name) {
            m_name = name;
        }

        std::string nation::get_prefix() const {
            return m_prefix;
        }

        void nation::set_prefix(const std::string &prefix) {
            m_prefix = prefix;
        }

        const std::vector<enemy_ptr> &nation::get_enemies() const {
            return m_enemies;
        }

        void nation::set_enemies(const std::vector<enemy_ptr> &enemies) {
            m_enemies = enemies;
        }

    }
}
