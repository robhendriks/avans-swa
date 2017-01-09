#ifndef CITY_DEFENCE_GAME_WORLD_H
#define CITY_DEFENCE_GAME_WORLD_H

#include <vector>
#include "../drawable/abstract_drawable_game_object.h"
#include "../game_level/game_level.h"

namespace domain {
    namespace gameworld {
        class game_world {
        public:
            game_world(std::vector<game_level::game_level*> game_levels);

            game_level::game_level *get_current_level();

            void set_current_level(int number);

            void go_to_next_level();

            bool has_next_level() const;

            unsigned int calculate_score() const;

            std::vector<game_level::game_level*> get_levels() const;

            ~game_world();

        private:
            std::vector<game_level::game_level*> m_levels;
            int m_current_level;
        };
    }
}

#endif //CITY_DEFENCE_GAME_WORLD_H
