//
// Created by Mark on 21-11-2016.
//

#include "nation.h"

namespace domain {
    namespace nations {
        nation::nation(const std::string &id, const std::string &name, std::string &prefix)
            : m_id{id}, m_name{name}, m_prefix{prefix} {}

        std::string nation::get_id() const {
            return m_id;
        }

        std::string nation::get_name() const {
            return m_name;
        }

        std::string nation::get_prefix() const {
            return m_prefix;
        }

        std::vector<std::shared_ptr<enemy>> nation::get_enemies() const {
            return m_enemies;
        }

        void nation::set_enemies(const std::vector<std::shared_ptr<enemy>> &enemies) {
            m_enemies = enemies;
        }

    }
}
