#ifndef CITY_DEFENCE_GAME_WORLD_CPP
#define CITY_DEFENCE_GAME_WORLD_CPP
#include "game_world.h"

namespace domain {
    namespace gameworld{

        lvl_id_and_game_stats::lvl_id_and_game_stats(game_level::game_stats &stat1) : stat(stat1) {

        }

        game_world::game_world(game_level::game_level &game_level) : m_level(&game_level) {}

        game_world::~game_world() {}

        game_level::game_level &game_world::get_current_level()  {
            return *m_level;
        }

        void game_world::set_current_level(game_level::game_level &game_lvl, bool tranfer_stats) {
            if(tranfer_stats) {
                lvl_id_and_game_stats s(m_level->get_stats());
                s.id = m_level->get_id();
                s.name = m_level->get_name();

                m_all_stats.push_back(std::make_unique<lvl_id_and_game_stats>(s));
            }

            m_level = &game_lvl;
        }

        std::vector<std::unique_ptr<lvl_id_and_game_stats>> const& game_world::get_stats_of_previous_lvls() {
            return m_all_stats;
        }
    }
}
#endif //CITY_DEFENCE_GAME_WORLD_CPP
