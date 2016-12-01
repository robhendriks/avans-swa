//
// Created by te on 17-Nov-16.
//

#include "game_level.h"
#include "../map/objects/building.h"
#include "../map/objects/road.h"

namespace domain {
    namespace game_level {
        game_level::game_level(std::string name, std::shared_ptr<domain::map::map> map, std::shared_ptr<game_stats> goal,
                               std::shared_ptr<domain::nations::nation> _enemies,
            engine::draganddrop::drag_and_drop &drag_and_drop) : m_name(name), m_map(map), m_goal(goal), m_start_time(0), m_drag_and_drop(drag_and_drop) {

            // Add all empty fields as dropable
            for (auto field : m_map->get_empty_fields()) {
                m_drag_and_drop.add_dropable(*field);
            }

            m_map->add_observer(this);
            m_stats = std::shared_ptr<game_stats>(new game_stats());
            m_enemy = _enemies;
        }

        std::string game_level::get_name() {
            return m_name;
        }

        std::shared_ptr<domain::map::map> game_level::get_map() {
            return m_map;
        }

        void game_level::draw(engine::graphics::texture_manager &texture_manager, unsigned int time_elapsed) {
            m_map->draw(texture_manager, time_elapsed);

            for (auto &obj : m_placeable_objects) {
                //obj->set_box();
                obj->draw(texture_manager, time_elapsed);
            }
        }

        void game_level::unload(engine::graphics::texture_manager &texture_manager) {
            m_map->unload(texture_manager);
        }

        std::shared_ptr<game_stats> game_level::get_goal() {
            return m_goal;
        }

        std::shared_ptr<game_stats> game_level::get_stats() {
            return m_stats;
        }

        // update stats
        void game_level::notify(domain::map::map * p_observee, std::string title) {
            if(title == "object-placed") {
                long building_count = 0;
                long road_count = 0;
                auto d = p_observee->get_fields_with_objects();
                for(std::shared_ptr<domain::map::field>& f : d){
                    if(dynamic_cast<domain::map::objects::building*>(f->get_object()))
                        ++building_count;
                    else if(dynamic_cast<domain::map::objects::road*>(f->get_object()))
                        ++road_count;
               }

                m_stats->set_built_building_count(building_count);
                m_stats->set_built_roads_count(road_count);
                m_stats->set_built_objects_count(road_count + building_count);
            }
        }

        bool game_level::is_goal_reached() {
            return *m_stats.get() >= *m_goal.get();
        }

        bool game_level::is_game_over(unsigned int current_duration) {
            int playing_time = current_duration - m_start_time;
            return  m_goal->get_max_duration() - playing_time < 0;
        }

        unsigned int game_level::get_start_time() {
            return m_start_time;
        }

        void game_level::set_start_time(unsigned int time) {
            m_start_time = time;
        }

        void game_level::add_placeable_object(map::objects::dragable_field_object &obj) {
            // Observe the placeable field
            obj.add_observer(this);
            // Add as dragable
            m_drag_and_drop.add_dragable(obj);

            m_placeable_objects.push_back(&obj);
        }

        void game_level::remove_placeable_object(map::objects::dragable_field_object &obj) {
            // Stop observing
            obj.remove_observer(this);

            // Erase from vector
            m_placeable_objects.erase(std::remove(m_placeable_objects.begin(), m_placeable_objects.end(), &obj), m_placeable_objects.end());
        };

        std::vector<std::shared_ptr<domain::nations::enemy>> game_level::get_enemies_in_lvl() {
            return m_enemies_in_lvl;
        }

        void game_level::set_enemies_in_lvl(std::vector<std::shared_ptr<domain::nations::enemy>> enemies) {
            m_enemies_in_lvl = enemies;
        }

        /**
         * Notified when a dragable_field_object is dropped
         *
         * @param p_observee
         * @param title
         */
        void game_level::notify(domain::map::objects::dragable_field_object *p_observee, std::string title) {
            if (title == "object-dropped") {
                // Remove from placeable_objects
                remove_placeable_object(*p_observee);

                // Create a copy of the placed field
                auto *copy = p_observee->clone();
                add_placeable_object(*copy);

                // Immediately start with dragging
                m_drag_and_drop.set_dragging(*copy);
            }
        }

        void game_level::set_peace_period(long ms_period) {
            m_peace_period = ms_period;
        }

        long game_level::get_peace_period() {
            return m_peace_period;
        }

        void game_level::set_waves_interval(long ms_interval) {
            m_waves_interval = ms_interval;
        }

        long game_level::get_waves_interval() {
            return m_waves_interval;
        }

        void game_level::set_base_wave_opportunity(double base_opportunity) {
            m_base_wave_opportunity = base_opportunity;
        }

        double game_level::get_base_wave_base_opportunity() {
            return m_base_wave_opportunity;
        }

        void game_level::set_wave_opportunity_increase(double increase) {
            m_wave_opportunity_increase = increase;
        }

        double game_level::get_wave_opportunity_increase() {
            return m_wave_opportunity_increase;
        }

        void game_level::set_wave_spawn_time_range(long ms_range) {
            m_wave_spawn_time_range = ms_range;
        }

        long game_level::get_wave_spawn_time_range() {
            return m_wave_spawn_time_range;
        }

        void game_level::set_enemy_nation(std::shared_ptr<domain::nations::nation> enemy) {
            m_enemy = enemy;
        }

        std::shared_ptr<domain::nations::nation> game_level::get_enemy_nation() {
            return m_enemy;
        }

        void game_level::set_spawn_bosses(bool bosses) {
            m_spawn_bosses = bosses;
        }

        bool game_level::get_spawn_bosses() {
            return m_spawn_bosses;
        }
    }
}
