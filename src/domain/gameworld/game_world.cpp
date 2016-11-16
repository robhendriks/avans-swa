#ifndef CITY_DEFENCE_GAME_WORLD_CPP
#define CITY_DEFENCE_GAME_WORLD_CPP
#include "game_world.h"
#include "../map/map.h"

namespace domain {
    namespace gameworld{
        game_world::game_world(std::vector<map::base_map*>& map) : _map(map) {
            _current_lvl = 0;
            auto m = map;
            domain::map::map* r = (domain::map::map*) m.at(0);
            r->get_tile_height();

            auto s = _map;
            domain::map::map* d = (domain::map::map*) s.at(0);
            d->get_tile_height();
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
            auto*  t = this->_map.at(this->_current_lvl);
            domain::map::map* m = (domain::map::map*) t;
            auto r = m->get_fields();
            int s = r.size();
            s++;
            return this->_map.at((unsigned int) this->_current_lvl);
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


    }
}
#endif //CITY_DEFENCE_GAME_WORLD_CPP
