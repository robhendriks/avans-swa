//
// Created by te on 17-Nov-16.
//

#include "game_level.h"

namespace domain {
    namespace game_level {
        game_level::game_level(std::string name, std::shared_ptr<domain::map::map> map, std::shared_ptr<game_stats> goal,
                               std::vector<std::pair<int, std::shared_ptr<domain::nations::enemy>>> _enemies,
            engine::draganddrop::drag_and_drop &drag_and_drop) : m_name(name), m_map(map), m_goal(goal), m_start_time(0), m_drag_and_drop(drag_and_drop) {

            // Add all empty fields as dropable
            for (auto field : m_map->get_empty_fields()) {
                m_drag_and_drop.add_dropable(*field);
            }

            m_map->add_observer(this);
            m_stats = std::shared_ptr<game_stats>(new game_stats());
            enemies = _enemies;
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
                    domain::map::objects::field_object_type type = f->get_object()->get_type();
                    if(type == domain::map::objects::field_object_type::BUILDING)
                        ++building_count;
                    else if(type == domain::map::objects::field_object_type::ROAD)
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

        std::vector<std::pair<int, std::shared_ptr<domain::nations::enemy>>> game_level::getEnemies(){
            return enemies;
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
    }
}
