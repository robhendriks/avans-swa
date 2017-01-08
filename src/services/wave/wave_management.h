//
// Created by te on 30-Nov-16.
//

#ifndef CITY_DEFENCE_WAVE_MANAGEMENT_CONTAINER_H
#define CITY_DEFENCE_WAVE_MANAGEMENT_CONTAINER_H

#include "wavegenerator.h"

namespace services {
    namespace wave {
        class wave_management {
        public:
            wave_management(wavegenerator &wave_gen);

            std::vector<domain::nations::enemy*> get_enemies(unsigned int time);

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

            void set_spawnable_nation(domain::nations::nation &nation);

            domain::nations::nation *get_spawnable_nation();

            void set_spawn_bosses(bool bosses);

            bool get_spawn_bosses();

            wavegenerator &get_wave_generator();

            // reset (should be called after lvl is over)
            void reset();

        private:
            wavegenerator &m_wave_gen;

            long m_peace_period = 0;
            long m_peace_including_start_time;
            // interval between waves
            long m_waves_interval = 0;
            int m_last_spawned_wave_time = -1;
            //(base size of the wave)
            double m_base_wave_opportunity = 0;
            //(size increase from wave to wave)
            double m_wave_opportunity_increase = 0;

            // the opportunity currently based of base and opportunity increase
            double m_wave_opportunity = 0;
            // the time range in ms where all units of a single wave spawns. 1000 = all units of a wave spawn in a range of 1 sec
            long m_wave_spawn_time_range = 0;
            // spawn bosses?
            bool m_spawn_bosses = false;

            // time first call was made
            unsigned int start_time = 0;

            // the nation where units get spawned from
            domain::nations::nation *m_spawnable_nation;

            // used to do last_time - time to see the difference between when last unit has spawned.
            std::vector<std::pair<int, domain::nations::enemy*>> m_current_list;

            // when to spawn and what to spawn logic
            void spawn_logic(unsigned int time);
        };
    }
}

#endif //CITY_DEFENCE_WAVE_MANAGEMENT_CONTAINER_H
