#ifndef CITY_DEFENCE_GAME_WORLD_CPP
#define CITY_DEFENCE_GAME_WORLD_CPP
#include "game_world.h"

namespace domain {
    namespace gameworld{
        game_world::game_world(std::vector<map::base_map*> map) :_map(map){
            _current_lvl = 0;
        }

        game_world::game_world() {

        }
        game_world::~game_world() {
            for(map::base_map* map : this->_map)
                delete map;
        }

        void game_world::draw(engine::graphics::texture_manager &texture_manager, engine::math::box2_t &dest) {
            this->_map.at((unsigned int) this->_current_lvl)->draw(texture_manager, dest);
        }

        void game_world::unload(engine::graphics::texture_manager &texture_manager) {
            for(auto &m : this->_map)
                m->unload(texture_manager);
        }

        map::base_map* game_world::get_current_map() {
            return this->_map.at((unsigned int) this->_current_lvl);
        }

        int game_world::get_current_lvl() {
            return this->_current_lvl;
        }


    }
}
#endif //CITY_DEFENCE_GAME_WORLD_CPP
