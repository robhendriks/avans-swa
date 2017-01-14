//
// Created by te on 17-Nov-16.
//

#include "game_level.h"

#include "../map/objects/road.h"
#include "../../events/goal_reached.h"

namespace domain {
    namespace game_level {
        game_level::game_level(std::string name, domain::map::map &map,
                               game_stats &goal,
                               domain::nations::nation &_enemies,
                               engine::draganddrop::drag_and_drop &drag_and_drop, long duration) :
                m_name(name), m_max_duration(duration), m_map(map), m_goal(goal), m_start_time(0), m_end_time(-1),
                m_played_time(-1),
                m_drag_and_drop(drag_and_drop), m_enemy(_enemies), m_paused(true), m_state(TO_PLAY) {

            m_stats = new game_stats();

            m_map.set_game_level(*this);

            // Observe all fields, update the stats, add the drag and drop instance and make the empty fields dropable
            for (auto &field : m_map.get_fields()) {
                if (field) {
                    field->add_observer(this);

                    if (field->has_object()) {
                        field->set_drag_and_drop(&m_drag_and_drop);

                        auto *dragable = dynamic_cast<map::objects::dragable_field_object*>(field->get_object());
                        if (dragable) {
                            dragable->set_drag_and_drop(&m_drag_and_drop);
                        }

                        field->get_object()->update_game_stats(*m_stats, "object-placed");
                    } else {
                        m_drag_and_drop.add_dropable(*field);
                    }
                }
            }

            // Set all goals as not reached
            for (auto &g : m_goal.get()) {
                m_reached_goals[g.first] = false;
            }

            // Check if there are already some goals reached
            check_goals_reached();

            m_has_cheated = false;

            // Add a callback for the drag and drop
            drag_and_drop.add_on_drop_callback(
                    std::bind(&game_level::decrement_building_cost, this, std::placeholders::_1));
        }

        game_level::~game_level() {

            if (!m_paused) {
                pause();
            }

            clean_resources();

            delete &m_drag_and_drop;
            delete m_stats;
        }

        std::string game_level::get_name() {
            return m_name;
        }

        domain::map::map &game_level::get_map() {
            return m_map;
        }

        game_stats &game_level::get_goal() {
            return m_goal;
        }

        game_stats &game_level::get_stats() {
            return *m_stats;
        }

        bool game_level::is_goal_reached() {
            return *m_stats >= m_goal;
        }

        bool game_level::is_game_over(unsigned int current_time) {
            if (m_max_duration >= 0) {
                int playing_time = current_time - m_start_time;

                if (m_played_time > 0) {
                    playing_time += m_played_time;
                }

                return m_max_duration - playing_time < 0;
            }

            return false;
        }

        void game_level::set_played_time(int played_time) {
            m_played_time = played_time;
        }

        int game_level::get_start_time() const {
            return m_start_time;
        }

        void game_level::set_start_time(int time) {
            m_start_time = time;
        }

        void game_level::set_end_time(unsigned int time) {
            int duration = static_cast<int>(time) - m_start_time;

            if (m_played_time > 0) {
                duration += m_played_time;
            }

            if (duration > m_max_duration) {
                time = static_cast<unsigned int>(m_start_time) + (m_max_duration - (m_played_time > 0 ? m_played_time : 0));
            }

            m_end_time = time;
        }

        int game_level::get_duration() const {
            return m_end_time - m_start_time + (m_played_time > 0 ? m_played_time : 0);
        }

        void game_level::add_placeable_object(map::objects::dragable_field_object &obj, int index) {
            // Add as dragable
            m_drag_and_drop.add_dragable(obj);

            if (index < 0 || index >= m_placeable_objects.size()) {
                m_placeable_objects.push_back(&obj);
            } else {
                m_placeable_objects.insert(m_placeable_objects.begin() + index, &obj);
            }
        }

        int game_level::remove_placeable_object(map::objects::dragable_field_object &obj) {
            // Find the object
            auto found = std::find(m_placeable_objects.begin(), m_placeable_objects.end(), &obj);

            if (found != m_placeable_objects.end()) {
                int index = found - m_placeable_objects.begin();
                // Remove from vector
                m_placeable_objects.erase(found);

                return index;
            }

            return -1;
        };


        std::vector<map::objects::dragable_field_object *> game_level::get_placeable_objects() const {
            return m_placeable_objects;
        }

        std::vector<domain::nations::enemy*> game_level::get_enemies_in_lvl() {
            return m_enemies_in_lvl;
        }

        void game_level::set_enemies_in_lvl(std::vector<domain::nations::enemy*> enemies) {
            m_enemies_in_lvl = enemies;
        }

        void game_level::remove_enemy_in_lvl(const domain::nations::enemy &enemy) {
            auto it = std::find(m_enemies_in_lvl.begin(), m_enemies_in_lvl.end(), &enemy);
            if (it != m_enemies_in_lvl.end()) {
                m_enemies_in_lvl.erase(it);
            }
        }

        /**
         * Notified when a dragable_field_object is dropped
         *
         * @param p_observee
         * @param title
         */
        void game_level::notify(domain::map::field *p_observee, std::string title) {
            if (title == "object-placed") {
                // Check if it was a dragable
                auto object = dynamic_cast<domain::map::objects::dragable_field_object *>(p_observee->get_object());

                if (object) {
                    // Remove from placeable_objects
                    int index = remove_placeable_object(*object);

                    // Create a copy of the placed field
                    auto *copy = object->clone();
                    add_placeable_object(*copy, index);

                    // Add the event if it is a building
                    auto *building = dynamic_cast<domain::map::objects::building*>(copy);
                    if (building) {
                        engine::eventbus::eventbus::get_instance().subscribe(
                            dynamic_cast<engine::eventbus::subscriber<engine::events::mouse_motion>*>(building));
                    }

                    // Immediately start with dragging
                    //m_drag_and_drop.set_next_dragging(*copy);
                }
            }

            // Update the stats
            p_observee->get_object()->update_game_stats(*m_stats, title);

            check_goals_reached();
        }

        void game_level::check_goals_reached() {
            for (auto it = m_reached_goals.begin(); it != m_reached_goals.end(); it++) {
                // Check if the goal is reached
                if (m_stats->get_count(it->first) >= m_goal.get_count(it->first)) {
                    // Reached
                    if (it->second) {
                        // First time reached, fire the event
                        auto *event = new events::goal_reached(it->first);
                        engine::eventbus::eventbus::get_instance().fire(event);
                        delete event;

                        m_reached_goals[it->first] = true;
                    }
                } else {
                    // Not reached
                    if (it->second) {
                        m_reached_goals[it->first] = false;
                    }
                }
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

        domain::nations::nation &game_level::get_enemy_nation() {
            return m_enemy;
        }

        void game_level::set_spawn_bosses(bool bosses) {
            m_spawn_bosses = bosses;
        }

        bool game_level::get_spawn_bosses() {
            return m_spawn_bosses;
        }

        std::vector<domain::resources::resource*> game_level::get_resources() {
            return m_resources;
        }

        void game_level::set_resources(std::vector<domain::resources::resource*> resources) {
            clean_resources();

            m_resources = resources;
        }

        void game_level::update(bool no_resources) {
            //Check objects if they can be constructed regarding resources
            for (unsigned int i = 0; i < m_placeable_objects.size(); i++) {
                std::vector<domain::resources::resource*> building_requirement = dynamic_cast<domain::map::objects::building *>(m_placeable_objects[i])->get_required_resources();
                bool meets_requirement = true;
                for (unsigned int j = 0; j < building_requirement.size(); j++) {
                    for (auto resource_bank : m_resources) {
                        if (resource_bank->get_resource_type() == building_requirement[j]->get_resource_type()) {

                            meets_requirement = resource_bank->check_resource(building_requirement[j]->get_count());
                            break;
                        }
                    }

                    if (!meets_requirement) {
                        //One or more required resources don't meet the requirement amount; so remove from dragable.
                        m_drag_and_drop.remove_dragable(m_placeable_objects[i]);
                        get_placeable_objects()[i]->set_saturated({255, 0, 0});
                        break;
                    }

                    if (j == building_requirement.size() - 1 && m_placeable_objects[i]->get_saturated()[2] != 255) {
                        //Disallowed building now again meets the requirements. Set it back
                        m_drag_and_drop.add_dragable(*m_placeable_objects[i]);
                        get_placeable_objects()[i]->set_saturated({255, 255, 255});
                    }
                }
            }
            if (no_resources) return;
            m_map.update_objects(this);
        }

        void game_level::decrement_building_cost(engine::draganddrop::dragable &building) {

            //Decrement the resources the buildings needs.
            std::vector<domain::resources::resource*> resources_to_decrement = dynamic_cast<domain::map::objects::building *>(&building)->get_required_resources();
            for (auto resource_to_decrement : resources_to_decrement) {
                for (auto resource_bank : m_resources) {
                    if (resource_bank->get_resource_type() == resource_to_decrement->get_resource_type()) {
                        resource_bank->decrement_resource(resource_to_decrement->get_count());
                        break;
                    }
                }
            }

            //Calls update an additional time apart form the main cycle so resources are updates instantly after placeing building.
            update(true);
        }

        long game_level::get_max_duration() const {
            return m_max_duration;
        }

        void game_level::pause() {
            if (m_paused) {
                // Resume
                m_drag_and_drop.start();
                subscribe_buildings_to_event();

                m_paused = false;
            } else {
                // Pause
                m_drag_and_drop.stop();
                unsubscribe_buildings_to_event();

                m_paused = true;
            }
        }

        int game_level::get_id() {
            return m_id;
        }

        void game_level::set_id(int id) {
            m_id = id;
        }

        void game_level::execute_cheat(){
            m_has_cheated =true;
            for(auto resource_bank : m_resources){
                resource_bank->max_out_resource();
            }
            update(true);
        }

        void game_level::clean_resources() {
            for (auto &resource : m_resources) {
                delete resource;
            }
        }

        void game_level::subscribe_buildings_to_event() const {
            for (auto &obj : m_placeable_objects) {
                auto *building = dynamic_cast<domain::map::objects::building*>(obj);
                if (building) {
                    engine::eventbus::eventbus::get_instance().subscribe(
                        dynamic_cast<engine::eventbus::subscriber<engine::events::mouse_motion>*>(building));
                }
            }

            for (auto &field : m_map.get_fields()) {
                if (field != nullptr) {
                    auto *obj = field->get_object();
                    if (obj != nullptr) {
                        auto *building = dynamic_cast<domain::map::objects::building*>(obj);
                        if (building) {
                            engine::eventbus::eventbus::get_instance().subscribe(
                                dynamic_cast<engine::eventbus::subscriber<engine::events::mouse_motion>*>(building));
                        }
                    }
                }
            }
        }

        void game_level::unsubscribe_buildings_to_event() const {
            for (auto &obj : m_placeable_objects) {
                auto *building = dynamic_cast<domain::map::objects::building *>(obj);
                if (building) {
                    engine::eventbus::eventbus::get_instance().unsubscribe(
                        dynamic_cast<engine::eventbus::subscriber<engine::events::mouse_motion> *>(building));
                }
            }

            for (auto &field : m_map.get_fields()) {
                if (field != nullptr) {
                    auto *obj = field->get_object();
                    if (obj != nullptr) {
                        auto *building = dynamic_cast<domain::map::objects::building *>(obj);
                        if (building) {
                            engine::eventbus::eventbus::get_instance().unsubscribe(
                                dynamic_cast<engine::eventbus::subscriber<engine::events::mouse_motion> *>(building));
                        }
                    }
                }
            }
        }

        state game_level::get_state() const {
            return m_state;
        }

        void game_level::start() {
            m_state = PLAYING;

            // Pause to start the new level
            pause();
        }

        void game_level::stop() {
            m_state = DONE;

            // Set the end time for a loaded game
            if (m_end_time == -1 && m_played_time && m_start_time == 0) {
                m_end_time = m_played_time;
            }

            pause();
        }

        void game_level::transition() {
            m_state = TRANSITION;
        }

        int game_level::get_played_time() const {
            return m_played_time;
        }
    }
}
