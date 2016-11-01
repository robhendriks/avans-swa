//
// Created by robbie on 1-11-2016.
//

#ifndef CITY_DEFENCE_MAIN_MAP_MODEL_H
#define CITY_DEFENCE_MAIN_MAP_MODEL_H

#include "../../domain/gameworld/game_world.h"
#include "../../domain/map/base_field.h"

namespace gui {
    namespace models {
        struct main_map_model {
            std::vector<std::vector<domain::map::base_field>> tiles;
            int number_of_tiles;
            int tile_height;
            int tile_width;
        };
    }
}

#endif //CITY_DEFENCE_MAIN_MAP_MODEL_H
