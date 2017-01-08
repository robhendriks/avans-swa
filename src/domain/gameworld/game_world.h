#ifndef CITY_DEFENCE_GAME_WORLD_H
#define CITY_DEFENCE_GAME_WORLD_H

#include <vector>
#include "../drawable/abstract_drawable_game_object.h"
#include "../game_level/game_level.h"

namespace domain {
    namespace gameworld {
        struct lvl_id_and_game_stats {
            lvl_id_and_game_stats(game_level::game_stats &stat1);
            game_level::game_stats &stat;
            int id;
            std::string name;
        };

        class game_world {
        public:
            game_world(game_level::game_level &game_level);

            game_level::game_level &get_current_level();

            // tranfer_stats of current lvl to m_all_stats before setting new current lvl
            void set_current_level(game_level::game_level &game_lvl, bool tranfer_stats = true);

            std::vector<std::unique_ptr<lvl_id_and_game_stats>> const &get_stats_of_previous_lvls();

            ~game_world();

        private:
            game_level::game_level *m_level;
            std::vector<std::unique_ptr<lvl_id_and_game_stats>> m_all_stats;
        };
    }
}

#endif //CITY_DEFENCE_GAME_WORLD_H
