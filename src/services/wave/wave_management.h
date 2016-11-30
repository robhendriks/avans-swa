//
// Created by te on 30-Nov-16.
//

#ifndef CITY_DEFENCE_WAVE_MANAGEMENT_CONTAINER_H
#define CITY_DEFENCE_WAVE_MANAGEMENT_CONTAINER_H

#include "wavegenerator.h"

namespace services{
    namespace wave{
        class wave_management {
        public:
            wave_management(wavegenerator wave_gen);
            std::vector<std::shared_ptr<domain::nations::enemy>> get_enemies(unsigned int time);
        private:
            wavegenerator& m_wave_gen;

            // used to do last_time - time to see the difference between when last unit has spawned.
            unsigned int m_last_spawned_unit_time = 0;
            std::vector<std::pair<int, std::shared_ptr<domain::nations::enemy>>> m_current_wave;
        };
    }
}

#endif //CITY_DEFENCE_WAVE_MANAGEMENT_CONTAINER_H
