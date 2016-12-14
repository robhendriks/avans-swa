//
// Created by robbie on 1-11-2016.
//

#ifndef CITY_DEFENCE_MAIN_MAP_MODEL_H
#define CITY_DEFENCE_MAIN_MAP_MODEL_H

#include <vector>
#include <memory>
#include "../../domain/gameworld/game_world.h"

namespace gui {
    namespace models {
        struct main_map_model {
            std::unique_ptr<domain::gameworld::game_world> world;
            bool paused = false;
            std::vector<std::shared_ptr<domain::resources::resource>> previous_resource;
        };
    }
}

#endif //CITY_DEFENCE_MAIN_MAP_MODEL_H
