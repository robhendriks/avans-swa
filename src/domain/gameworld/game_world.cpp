#ifndef CITY_DEFENCE_GAME_WORLD_CPP
#define CITY_DEFENCE_GAME_WORLD_CPP
#include "game_world.h"

namespace domain {
    namespace gameworld{
        game_world::game_world(std::unique_ptr<game_level::game_level> game_level) : m_level(std::move(game_level)) {}

        game_world::~game_world() {}

        game_level::game_level &game_world::get_current_level()  {
            return *m_level;
        }

        void game_world::set_current_level(std::unique_ptr<game_level::game_level> game_lvl, bool tranfer_stats){
            if(tranfer_stats){
                lvl_id_stats_and_game_stats s;
                s.id = m_level->get_id();
                s.name = m_level->get_name();
                s.stat = m_level->get_stats();
                m_all_stats.push_back(s);
            }

            m_level = std::move(game_lvl);
        }

        std::vector<lvl_id_stats_and_game_stats> game_world::get_stats_of_previous_lvls() {
            return m_all_stats;
        }

    }
}
#endif //CITY_DEFENCE_GAME_WORLD_CPP
