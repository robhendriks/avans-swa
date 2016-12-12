#ifndef CITY_DEFENCE_GAME_WORLD_H
#define CITY_DEFENCE_GAME_WORLD_H

#include <vector>
#include "../drawable/abstract_drawable_game_object.h"
#include "../game_level/game_level.h"

namespace domain {
    namespace gameworld {
        class game_world {
        public:
            game_world(std::unique_ptr<game_level::game_level> game_level);
            game_level::game_level& get_current_level();
            // tranfer_stats of current lvl to m_all_stats before setting new current lvl
            void set_current_level(std::unique_ptr<game_level::game_level> game_lvl, bool tranfer_stats = true);
            // all lvl's or just the current one
            game_level::game_stats get_stats(bool all = false);
            ~game_world();

        private:
            std::unique_ptr<game_level::game_level> m_level;
            std::vector<std::shared_ptr<game_level::game_stats>> m_all_stats;
        };
    }
}

#endif //CITY_DEFENCE_GAME_WORLD_H
