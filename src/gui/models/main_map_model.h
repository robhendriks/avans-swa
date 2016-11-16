//
// Created by robbie on 1-11-2016.
//

#ifndef CITY_DEFENCE_MAIN_MAP_MODEL_H
#define CITY_DEFENCE_MAIN_MAP_MODEL_H

#include <vector>
#include "../../domain/map/base_field.h"
#include <memory>

namespace gui {
    namespace models {
        struct main_map_model {
            main_map_model() {};
            ~main_map_model() {
                delete map_box;
            }

            std::unique_ptr<domain::gameworld::game_world> world;
            engine::math::box2_t* map_box;
        };
    }
}

#endif //CITY_DEFENCE_MAIN_MAP_MODEL_H
