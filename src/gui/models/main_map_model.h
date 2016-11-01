//
// Created by robbie on 1-11-2016.
//

#ifndef CITY_DEFENCE_MAIN_MAP_MODEL_H
#define CITY_DEFENCE_MAIN_MAP_MODEL_H

#include <vector>
#include "../../domain/map/base_field.h"

namespace gui {
    namespace models {
        struct main_map_model {
            main_map_model() {};
            ~main_map_model() {
                delete map;
            }
            std::vector<std::vector<domain::map::base_field*>> tiles;
            int tile_height;
            int tile_width;
            engine::math::box2_t *map;
        };
    }
}

#endif //CITY_DEFENCE_MAIN_MAP_MODEL_H
