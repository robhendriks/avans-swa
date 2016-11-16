#ifndef CITY_DEFENCE_GAME_WORLD_H
#define CITY_DEFENCE_GAME_WORLD_H

#include <vector>
#include "../map/base_map.h"
#include "../drawable/abstract_drawable_game_object.h"

namespace domain {
    namespace gameworld {
        class game_world : public domain::drawable::abstract_drawable_game_object{
        public:
            game_world();

            game_world(std::vector<map::base_map*>& map);
            void draw(engine::graphics::texture_manager &texture_manager, engine::math::box2_t &dest);
            void unload(engine::graphics::texture_manager &texture_manager);
            map::base_map* get_current_map();
            int get_current_lvl();
            int next_level();
            void reset_level();
            ~game_world();

        private:
            int _current_lvl;
            std::vector<map::base_map*> _map;
        };
    }
}

#endif //CITY_DEFENCE_GAME_WORLD_H
