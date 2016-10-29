#ifndef CITY_DEFENCE_GAME_WORLD_H
#define CITY_DEFENCE_GAME_WORLD_H

#include <vector>
#include "../map/base_map.h"

namespace domain {
    namespace gameworld {
        class game_world {
        public:
            game_world();

            ~game_world();

        private:
            std::vector<map::base_map> _map;
        };
    }
}

#endif //CITY_DEFENCE_GAME_WORLD_H
