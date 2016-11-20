//
// Created by te on 17-Nov-16.
//

#ifndef CITY_DEFENCE_GAME_LEVEL_H
#define CITY_DEFENCE_GAME_LEVEL_H
#include "string"
#include "../map/base_map.h"
#include "game_stats.h"
#include <memory>

namespace domain{
    namespace  game_level {
        class game_level : public drawable::abstract_drawable_game_object, public engine::observer::observer<domain::map::base_map>{
        public:
            game_level(std::string &name, map::base_map *map, std::shared_ptr<game_stats>& goal);
            game_level(std::string &name, std::shared_ptr<map::base_map> map, std::shared_ptr<game_stats>& goal);
            std::string get_name();
            std::shared_ptr<domain::map::base_map> get_map();
            virtual void draw(engine::graphics::texture_manager &texture_manager, engine::math::box2_t &dest);
            virtual void unload(engine::graphics::texture_manager &texture_manager);
            virtual void notify(domain::map::base_map *p_observee, std::string title);
            virtual bool is_goal_reached();
            virtual bool is_game_over();
            std::shared_ptr<game_stats> get_goal();
            std::shared_ptr<game_stats> get_stats();
        private:
            std::string& m_name;
            std::shared_ptr<domain::map::base_map> m_map;
            std::shared_ptr<game_stats> m_goal;
            std::shared_ptr<game_stats> m_stats;
        };
    }
}

#endif //CITY_DEFENCE_GAME_LEVEL_H
