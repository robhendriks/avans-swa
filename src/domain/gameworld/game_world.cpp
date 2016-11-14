#ifndef CITY_DEFENCE_GAME_WORLD_CPP
#define CITY_DEFENCE_GAME_WORLD_CPP
#include "game_world.h"

namespace domain {
    namespace gameworld {
        game_world::game_world() {
            _current_lvl = 0;
        }

        game_world::~game_world() {
        }

        void game_world::draw(engine::graphics::texture_manager &texture_manager, engine::math::box2_t &dest) {
            this->_map.at(this->_current_lvl).draw(texture_manager, dest);
        }

        void game_world::unload(engine::graphics::texture_manager &texture_manager) {
            for(auto &m : this->_map)
                m.unload(texture_manager);
        }
    }
}
#endif //CITY_DEFENCE_GAME_WORLD_CPP
