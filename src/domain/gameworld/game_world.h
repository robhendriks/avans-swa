#ifndef CITY_DEFENCE_GAME_WORLD_H
#define CITY_DEFENCE_GAME_WORLD_H

#include <vector>
#include "../drawable/abstract_drawable_game_object.h"
#include "../game_level/game_level.h"

namespace domain {
    namespace gameworld {
        class game_world {
        public:
            game_world(std::vector<std::unique_ptr<game_level::game_level>> &game_levels);

            void unload(engine::graphics::texture_manager &texture_manager);

            game_level::game_level &get_current_level();

            game_level::game_level &next_level();

            bool has_next_level();

            game_level::game_stats get_stats();

            game_level::game_level &reset_level();

            ~game_world();

        private:
            unsigned int m_current_lvl;
            std::vector<std::unique_ptr<game_level::game_level>> &m_levels;
        };
    }
}

#endif //CITY_DEFENCE_GAME_WORLD_H
