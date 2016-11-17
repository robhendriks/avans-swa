#ifndef CITY_DEFENCE_GAME_WORLD_CPP
#define CITY_DEFENCE_GAME_WORLD_CPP
#include "game_world.h"
#include "../map/map.h"
#include <memory>

namespace domain {
    namespace gameworld{
        game_world::game_world(std::vector<std::shared_ptr<game_level::game_level>>& game_levels) : m_levels(game_levels) {
            _current_lvl = 0;
        }

        game_world::game_world() {

        }
        game_world::~game_world() {
        }

        void game_world::draw(engine::graphics::texture_manager &texture_manager, engine::math::box2_t &dest) {
            this->m_levels.at((unsigned int) this->_current_lvl)->draw(texture_manager, dest);
        }

        void game_world::unload(engine::graphics::texture_manager &texture_manager) {
            for(auto &m : this->m_levels)
                m->unload(texture_manager);
        }

        std::shared_ptr<game_level::game_level> game_world::get_current_level()  {
            return this->m_levels.at((unsigned int) this->_current_lvl);
        }

        std::shared_ptr<game_level::game_level> game_world::reset_level() {
            this->_current_lvl = 0;
            return this->get_current_level();
        }

        std::shared_ptr<game_level::game_level> game_world::next_level() {
            this->_current_lvl++;
            return this->get_current_level();
        }
    }
}
#endif //CITY_DEFENCE_GAME_WORLD_CPP
