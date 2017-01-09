//
// Created by robbie on 8-1-2017.
//

#ifndef CITY_DEFENCE_BASE_WORLD_SAVER_H
#define CITY_DEFENCE_BASE_WORLD_SAVER_H

#include "../../domain/gameworld/game_world.h"

namespace services {
    namespace world_saver {
        class base_world_saver {
        public:
            virtual void save(domain::gameworld::game_world &world) = 0;

            virtual ~base_world_saver() = default;
        };
    }
}

#endif //CITY_DEFENCE_BASE_WORLD_SAVER_H
