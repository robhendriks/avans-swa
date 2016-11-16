//
// Created by Leendert on 14-11-2016.
//

#ifndef CITY_DEFENCE_BASE_MAP_LOADER_H
#define CITY_DEFENCE_BASE_MAP_LOADER_H
#include <string>
#include "../../domain/gameworld/game_world.h"

namespace services {
    namespace level_loader {
        class base_map_loader {
        public:
            virtual domain::gameworld::game_world *load(std::string file_location) = 0;
        };
    };
};


#endif //CITY_DEFENCE_BASE_MAP_LOADER_H
