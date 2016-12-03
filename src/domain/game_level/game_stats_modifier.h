//
// Created by robbie on 2-12-2016.
//

#ifndef CITY_DEFENCE_GAME_STATS_MODIFIER_H
#define CITY_DEFENCE_GAME_STATS_MODIFIER_H

#include "game_stats.h"

namespace domain {
    namespace game_level {
        class game_stats;
    }
}

namespace domain {
    namespace game_level {
        class game_stats_modifier {
        public:
            virtual void update_game_stats(game_stats &game_stats1) = 0;
        };
    }
}

#endif //CITY_DEFENCE_GAME_STATS_MODIFIER_H
