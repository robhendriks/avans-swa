//
// Created by te on 17-Nov-16.
//

#ifndef CITY_DEFENCE_GAME_LEVEL_H
#define CITY_DEFENCE_GAME_LEVEL_H

#include <memory>
#include "string"
#include "game_stats.h"
#include "../drawable/abstract_drawable_game_object.h"
#include "../map/map.h"
#include "../../engine/events/game_tick.h"
#include "../nations/enemy.h"


namespace domain {
    namespace game_level {
        class game_level
            : public drawable::abstract_drawable_game_object, public engine::observer::observer<domain::map::map> {
        public:
            game_level(std::string name, std::shared_ptr<map::map> map, std::shared_ptr<game_stats> goal,
                       std::vector<std::pair<int, std::shared_ptr<domain::nations::enemy>>> _enemies,
                       engine::draganddrop::drag_and_drop &drag_and_drop);

            std::string get_name();

            std::shared_ptr<domain::map::map> get_map();

            virtual void draw(engine::graphics::texture_manager &texture_manager, unsigned int time_elapsed);

            virtual void unload(engine::graphics::texture_manager &texture_manager);

            virtual void notify(domain::map::map *p_observee, std::string title);

            virtual bool is_goal_reached();

            virtual bool is_game_over(unsigned int current_duration);

            std::shared_ptr<game_stats> get_goal();

            std::shared_ptr<game_stats> get_stats();

            unsigned int get_start_time();

            void set_start_time(unsigned int time);

            std::vector<std::pair<int, std::shared_ptr<domain::nations::enemy>>> getEnemies();

            void add_placeable_object(map::objects::object &obj);

        private:
            std::string m_name;
            std::shared_ptr<domain::map::map> m_map;
            std::shared_ptr<game_stats> m_goal;
            std::shared_ptr<game_stats> m_stats;
            unsigned int m_start_time;
            std::vector<std::pair<int, std::shared_ptr<domain::nations::enemy>>> enemies;
            std::vector<map::objects::field_object *> m_placeable_objects;
            engine::draganddrop::drag_and_drop &m_drag_and_drop;
        };
    }
}

#endif //CITY_DEFENCE_GAME_LEVEL_H
