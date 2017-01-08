//
// Created by Mark on 21-11-2016.
//

#include "nation.h"

namespace domain {
    namespace nations {
        nation::nation(std::string _name, std::string _prefix_name) {
            m_name = _name;
            m_prefix_name = _prefix_name;
        }

        void nation::set_available_enemies(std::vector<enemy*> _enemies) {
            m_enemies = _enemies;
        }

        std::string nation::get_name() {
            return m_name;
        }

        std::string nation::get_prefix_name() {
            return m_prefix_name;
        }

        std::vector<enemy*> nation::get_available_enemies() {
            return m_enemies;
        }

        nation::~nation() {
        }

    }
}
