#ifndef CITY_DEFENCE_GAME_WORLD_CPP
#define CITY_DEFENCE_GAME_WORLD_CPP
#include "game_world.h"

namespace domain {
    namespace gameworld{
        game_world::game_world(std::vector<std::unique_ptr<game_level::game_level>>& game_levels) : m_levels(game_levels) {
           m_current_lvl = 0;
        }

        game_world::~game_world() {
        }

        void game_world::draw(engine::graphics::texture_manager &texture_manager, unsigned int time_elapsed) {
            this->m_levels.at(m_current_lvl)->draw(texture_manager, time_elapsed);
        }

        void game_world::unload(engine::graphics::texture_manager &texture_manager) {
            for(auto &m : m_levels)
                m->unload(texture_manager);
        }

        game_level::game_level &game_world::get_current_level()  {
            return *m_levels.at(m_current_lvl).get();
        }

        game_level::game_level &game_world::reset_level() {
            m_current_lvl = 0;
            return get_current_level();
        }

        game_level::game_level &game_world::next_level() {
            m_current_lvl++;
            return get_current_level();
        }

        bool game_world::has_next_level() {
            return m_current_lvl < m_levels.size();
        }

        game_level::game_stats game_world::get_stats() {
            game_level::game_stats stats;

            for(auto &l: m_levels){
                stats = stats + *l->get_stats();
            }

            return stats;
        }
    }
}
#endif //CITY_DEFENCE_GAME_WORLD_CPP
