//
// Created by Leendert on 14-11-2016.
//

#ifndef CITY_DEFENCE_BASE_MAP_LOADER_H
#define CITY_DEFENCE_BASE_MAP_LOADER_H
#include <string>
#include "../../domain/gameworld/game_world.h"

namespace services {
    namespace level_loader {
        class base_level_loader {
        public:
            virtual std::unique_ptr<domain::game_level::game_level> load(int id) = 0;
            virtual int get_level_count() = 0;
            virtual ~base_level_loader() = default;
        };
    };
};


#endif //CITY_DEFENCE_BASE_MAP_LOADER_H
