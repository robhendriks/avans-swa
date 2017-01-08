#ifndef CITY_DEFENCE_GAME_WORLD_CPP
#define CITY_DEFENCE_GAME_WORLD_CPP
#include "game_world.h"

namespace domain {
    namespace gameworld{

        game_world::game_world(std::vector<game_level::game_level*> game_levels) :
            m_levels(game_levels), m_current_level(0) {}

        game_world::~game_world() {
            // Remove all levels
            for (auto &level : m_levels) {
                delete level;
            }
        }

        game_level::game_level &game_world::get_current_level()  {
            return *m_levels[m_current_level];
        }

        void game_world::set_current_level(unsigned int number) {
            if (number < m_levels.size()) {
                m_current_level = number;
            }
        }

        unsigned int game_world::calculate_score() const {
            unsigned int score = 0;
            for (auto &level : m_levels) {
                score += level->get_max_duration() - level->get_duration();
            }

            return score;
        }

        bool game_world::has_next_level() const {
            return m_current_level + 1 < m_levels.size();
        }

        void game_world::go_to_next_level() {
            if (has_next_level()) {
                m_current_level++;
            }
        }
    }
}
#endif //CITY_DEFENCE_GAME_WORLD_CPP
