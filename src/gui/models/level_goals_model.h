//
// Created by robbie on 2-12-2016.
//

#ifndef CITY_DEFENCE_LEVEL_GOALS_MODEL_H
#define CITY_DEFENCE_LEVEL_GOALS_MODEL_H

#include <memory>
#include "../../domain/game_level/game_stats.h"

namespace gui {
    namespace models {
        struct level_goals_model {
            std::shared_ptr<domain::game_level::game_stats> game_goals;
            std::shared_ptr<domain::game_level::game_stats> game_stats;
        };
    }
}

#endif //CITY_DEFENCE_LEVEL_GOALS_MODEL_H
