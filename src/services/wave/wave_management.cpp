//
// Created by te on 30-Nov-16.
//

#include <algorithm>
#include "wave_management.h"
namespace services {
    namespace wave {
        wave_management::wave_management(std::shared_ptr<wavegenerator> wave_gen) : m_wave_gen(wave_gen)
        {
            m_current_list = {};
        }

        std::vector<std::shared_ptr<domain::nations::enemy>> wave_management::get_enemies(unsigned int time) {

            // set start time and the end of peace time in case its the first call
            if(start_time == 0){
                start_time = time;
                m_peace_including_start_time = static_cast<long>(start_time) + m_peace_period;
            }

            // set values we are going to use
            auto return_list = std::vector<std::shared_ptr<domain::nations::enemy>>();

            // in case there is still peace time just do nothing
            if(m_peace_including_start_time > static_cast<int>(time)){
                return return_list;
            }
            else{
                // spawn wave logic for spawning waves
                spawn_logic(time);

                // make subset
                for(auto pair : m_current_list){
                    bool result = pair->first < static_cast<int>(time);
                    if(result){
                        return_list.push_back(pair->second);
                    };
                }

                // now remove them from the list of the enemies that haven't been given back yet.
                auto new_end = std::remove_if(m_current_list.begin(), m_current_list.end(),
                                              [time, return_list](std::shared_ptr<std::pair<int, std::shared_ptr<domain::nations::enemy>>>& pair)
                                              { return pair->first > static_cast<int>(time);});

                m_current_list.erase(new_end, m_current_list.end());

                return return_list;
            }
        }



        void wave_management::spawn_logic(unsigned int time) {

            /**
             * visually representation of this if
             *time/last_spawn/spawn or not
             * 0     -1          spawn
             * 1     0
             * 2     0
             * 20    0
             * 22    0           spawn
             * 23    22
             */
            if(m_last_spawned_wave_time == -1 || static_cast<int>(time) -  m_last_spawned_wave_time  >= m_waves_interval){
                m_last_spawned_wave_time = time;

                // generate wave
                auto new_enemies = m_wave_gen->generateEnemies(m_wave_spawn_time_range, static_cast<int>(m_wave_opportunity), *m_spawnable_nation.get(), false ,0, m_spawn_bosses);

                for(auto& pair : new_enemies){
                    // update the time so current time gets attached
                    pair.first += time;
                    m_current_list.push_back(std::make_shared<std::pair<int, std::shared_ptr<domain::nations::enemy>>>(pair));
                }

                // increasing opportunity logic for next wave.
                m_wave_opportunity += m_wave_opportunity_increase;
            }
        }

        void wave_management::set_peace_period(long ms_period) {
            m_peace_period = ms_period;
        }

        long wave_management::get_peace_period() {
            return m_peace_period;
        }

        void wave_management::set_waves_interval(long ms_interval) {
            m_waves_interval = ms_interval;
        }

        long wave_management::get_waves_interval() {
            return m_waves_interval;
        }

        void wave_management::set_base_wave_opportunity(double base_opportunity) {
            m_base_wave_opportunity = base_opportunity;

            // in case a wave isn't underway then set is as base
            if(m_wave_opportunity == 0)
                m_wave_opportunity = m_base_wave_opportunity;
        }

        double wave_management::get_base_wave_base_opportunity() {
            return m_base_wave_opportunity;
        }

        void wave_management::set_wave_opportunity_increase(double increase) {
            m_wave_opportunity_increase = increase;
        }

        double wave_management::get_wave_opportunity_increase() {
            return m_wave_opportunity_increase;
        }

        void wave_management::set_wave_spawn_time_range(long ms_range) {
            m_wave_spawn_time_range = ms_range;
        }

        long wave_management::get_wave_spawn_time_range() {
            return m_wave_spawn_time_range;
        }

        void wave_management::set_spawnable_nation(std::shared_ptr<domain::nations::nation> nation) {
            m_spawnable_nation = nation;
        }

        std::shared_ptr<domain::nations::nation> wave_management::get_spawnable_nation() {
            return m_spawnable_nation;
        }

        void wave_management::set_spawn_bosses(bool bosses) {
            m_spawn_bosses = bosses;
        }

        bool wave_management::get_spawn_bosses() {
            return m_spawn_bosses;
        }

        void wave_management::reset() {
            m_wave_opportunity = m_base_wave_opportunity;
            m_current_list.clear();
            start_time = 0;
        }
    }
}