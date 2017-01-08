//
// Created by te on 17-Nov-16.
//

#ifndef CITY_DEFENCE_GAME_LEVEL_H
#define CITY_DEFENCE_GAME_LEVEL_H

#include <memory>
#include "string"
#include "game_stats.h"
#include "../map/map.h"
#include "../nations/enemy.h"
#include "../resources/resource.h"
#include "../map/objects/dragable_field_object.h"
#include "../map/objects/building.h"


namespace domain {
    namespace game_level {
        class game_level : public engine::observer::observer<domain::map::field> {
        public:
            game_level(std::string name, std::shared_ptr<map::map> map, std::shared_ptr<game_stats> goal,
                       std::shared_ptr<domain::nations::nation> _enemies,
                       engine::draganddrop::drag_and_drop &drag_and_drop, long duration);

            std::string get_name();

            std::shared_ptr<domain::map::map> get_map();

            virtual void notify(domain::map::field *p_observee, std::string title);

            virtual bool is_goal_reached();

            virtual bool is_game_over(unsigned int current_duration);

            int get_id();
            void set_id(int id);

            std::shared_ptr<game_stats> get_goal();

            std::shared_ptr<game_stats> get_stats();

            unsigned int get_start_time();

            void set_start_time(unsigned int time);

            long get_max_duration() const;

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

            /**
             * Pause or resume the game level
             */
            void pause();

            std::vector<std::shared_ptr<domain::resources::resource>> get_resources();

            void set_resources(std::vector<std::shared_ptr<domain::resources::resource>> resources);

            void update(bool no_resources = false);

            void decrement_building_cost(engine::draganddrop::dragable& building);

            void execute_cheat();

        private:
            void check_goals_reached();
            int m_id = 0;

            std::map<std::string, bool> m_reached_goals;

            std::string m_name;
            long m_max_duration;
            std::shared_ptr<domain::map::map> m_map;
            std::shared_ptr<game_stats> m_goal;
            std::shared_ptr<game_stats> m_stats;
            unsigned int m_start_time;
            std::vector<std::pair<int, std::shared_ptr<domain::nations::enemy>>> enemies;
            std::vector<map::objects::dragable_field_object *> m_placeable_objects;
            engine::draganddrop::drag_and_drop &m_drag_and_drop;

            std::vector<std::shared_ptr<domain::nations::enemy>> m_enemies_in_lvl;

            //List of the resources
            std::vector<std::shared_ptr<domain::resources::resource>> m_resources;

            //(initial periode where no waves spawn in ms)
            long m_peace_period = 0;
            // interval between waves
            long m_waves_interval = 30000;
            //(base size of the wave)
            double m_base_wave_opportunity = 10;
            //(size increase from wave to wave)
            double m_wave_opportunity_increase = 0;
            // the time range in ms where all units of a single wave spawns. 1000 = all units of a wave spawn in a range of 1 sec
            long m_wave_spawn_time_range = 3000;
            // nation where enemies get spawned from
            std::shared_ptr<domain::nations::nation> m_enemy;
            // spawn boss units
            bool m_spawn_bosses = true;

            bool m_paused;

            bool m_has_cheated;
        };
    }
}

#endif //CITY_DEFENCE_GAME_LEVEL_H
