#ifndef CITY_DEFENCE_GAME_WORLD_CPP
#define CITY_DEFENCE_GAME_WORLD_CPP
#include "game_world.h"

namespace domain {
    namespace gameworld{
        game_world::game_world(std::unique_ptr<game_level::game_level> game_level) : m_level(std::move(game_level)) {
            set_mayor(nullptr);
        }

        game_world::~game_world() {}

        game_level::game_level & game_world::get_current_level()  {
            return *m_level;
        }

        void game_world::set_current_level(std::unique_ptr<game_level::game_level> game_lvl, bool tranfer_stats){
            if(tranfer_stats){
                lvl_id_and_game_stats s;
                s.id = m_level->get_id();
                s.name = m_level->get_name();
                s.stat = m_level->get_stats();
                m_all_stats.push_back(std::make_unique<lvl_id_and_game_stats>(s));
            }

            m_level = std::move(game_lvl);
        }

        std::vector<std::unique_ptr<lvl_id_and_game_stats>> const& game_world::get_stats_of_previous_lvls() {
            return m_all_stats;
        }

        std::shared_ptr<mayor> game_world::get_mayor() const {
            return m_mayor;
        }

        void game_world::set_mayor(const std::shared_ptr<mayor> _mayor) {
            if(_mayor == nullptr)
            {
                mayor ravanna = mayor("Ravanna", {"Playing dictator"}, {"Aggresive", "Conquest orientated"});
                milestone milestone1 = milestone();
                milestone1.min = 4;
                milestone1.max = 4;
                milestone1.responses = {"This is only the beginning my servant."};
                milestone_group group1 = milestone_group();
                group1.display_name = "Buildings";
                group1.counter_name = "buildings";
                group1.milestones = {milestone1};
                ravanna.add_milestone_group(group1);
            }
            else{
                m_mayor = _mayor;
            }
    }

}
}
#endif //CITY_DEFENCE_GAME_WORLD_CPP
