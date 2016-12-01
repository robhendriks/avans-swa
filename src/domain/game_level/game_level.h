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
#include "../map/objects/dragable_field_object.h"


namespace domain {
    namespace game_level {
        class game_level : public engine::observer::observer<domain::map::map>,
                           public engine::observer::observer<domain::map::objects::dragable_field_object> {
        public:
            game_level(std::string name, std::shared_ptr<map::map> map, std::shared_ptr<game_stats> goal,
                       std::vector<std::pair<int, std::shared_ptr<domain::nations::nation>>> _nations,
                       engine::draganddrop::drag_and_drop &drag_and_drop);

            std::string get_name();

            std::shared_ptr<domain::map::map> get_map();

            virtual void unload(engine::graphics::texture_manager &texture_manager);

            virtual void notify(domain::map::map *p_observee, std::string title);

            virtual void notify(domain::map::objects::dragable_field_object *p_observee, std::string title);

            virtual bool is_goal_reached();

            virtual bool is_game_over(unsigned int current_duration);

            std::shared_ptr<game_stats> get_goal();

            std::shared_ptr<game_stats> get_stats();

            unsigned int get_start_time();

            void set_start_time(unsigned int time);

            void add_placeable_object(map::objects::dragable_field_object &obj);

            void remove_placeable_object(map::objects::dragable_field_object &obj);

            std::vector<map::objects::dragable_field_object *> get_placeable_objects() const;

            std::vector<std::shared_ptr<domain::nations::enemy>> get_enemies_in_lvl();

            void set_enemies_in_lvl(std::vector<std::shared_ptr<domain::nations::enemy>> enemies);

            void set_peace_period(long ms_period);

            long get_peace_period();

            void set_waves_interval(long ms_interval);

            long get_waves_interval();

            void set_base_wave_opportunity(double base_opportunity);

            double get_base_wave_base_opportunity();

            void set_wave_opportunity_increase(double increase);

            double get_wave_opportunity_increase();

            void set_wave_spawn_time_range(long ms_range);

            long get_wave_spawn_time_range();

            void set_enemy_nation(std::shared_ptr<domain::nations::nation> enemy);

            std::shared_ptr<domain::nations::nation> get_enemy_nation();

            void set_spawn_bosses(bool bosses);

            bool get_spawn_bosses();

        private:
            std::string m_name;
            std::shared_ptr<domain::map::map> m_map;
            std::shared_ptr<game_stats> m_goal;
            std::shared_ptr<game_stats> m_stats;
            unsigned int m_start_time;
            std::vector<std::pair<int, std::shared_ptr<domain::nations::enemy>>> enemies;
            std::vector<map::objects::dragable_field_object *> m_placeable_objects;
            engine::draganddrop::drag_and_drop &m_drag_and_drop;
        };
    }
}

#endif //CITY_DEFENCE_GAME_LEVEL_H
