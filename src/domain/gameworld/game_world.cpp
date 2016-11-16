#ifndef CITY_DEFENCE_GAME_WORLD_CPP
#define CITY_DEFENCE_GAME_WORLD_CPP
#include "game_world.h"
#include "../map/map.h"

namespace domain {
    namespace gameworld{
        game_world::game_world(std::vector<map::base_map*> maps) :_maps(maps){
            _current_lvl = 0;
            auto m = maps;
            domain::map::map* r = (domain::map::map*) m.at(0);
            r->get_tile_height();

            auto s = _maps;
            domain::map::map* d = (domain::map::map*) s.at(0);
            d->get_tile_height();
        }

        game_world::game_world() {

        }
        game_world::~game_world() {
            for(map::base_map* map : this->_maps)
                delete map;
        }

        void game_world::draw(engine::graphics::texture_manager &texture_manager, engine::math::box2_t &dest) {
            this->_maps.at((unsigned int) this->_current_lvl)->draw(texture_manager, dest);
        }

        void game_world::unload(engine::graphics::texture_manager &texture_manager) {
            for(auto &m : this->_maps)
                m->unload(texture_manager);
        }

        map::base_map* game_world::get_current_map() {
            auto*  t = this->_maps.at((unsigned int) this->_current_lvl);
            domain::map::map* m = (domain::map::map*) t;
            auto r = m->get_fields();
            int s = r.size();
            s++;
            return this->_maps.at((unsigned int) this->_current_lvl);
        }

        int game_world::get_current_lvl() {
            return this->_current_lvl;
        }

        void game_world::reset_level() {
            this->_current_lvl = 0;
        }

        int game_world::next_level() {
            this->_current_lvl++;
            return this->_current_lvl;
        }

        game_world &game_world::operator=(game_world obj) {
            this->_current_lvl = obj._current_lvl;
            this->_maps = obj._maps;
            domain::map::map* d = (domain::map::map*)this->_maps.at(0);
            d->get_tile_height();
            return *this;
        }
    }
}
#endif //CITY_DEFENCE_GAME_WORLD_CPP
