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
            if(tranfer_stats) m_all_stats.push_back(m_level->get_stats());
            m_level = std::move(game_lvl);
        }

        game_level::game_stats game_world::get_stats(bool all) {
            game_level::game_stats stat;

            if(all){
                for(auto lvl_stat : m_all_stats)
                    stat = stat + *lvl_stat;
            }
            else{
                stat = *m_level->get_stats();
            }

            return stat;
        }
    }
}
#endif //CITY_DEFENCE_GAME_WORLD_CPP
