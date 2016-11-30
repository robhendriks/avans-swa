//
// Created by te on 30-Nov-16.
//

#include "wave_management.h"
namespace services {
    namespace wave {
        wave_management::wave_management(wavegenerator wave_gen) : m_wave_gen(wave_gen) {

        }

        std::vector<std::shared_ptr<domain::nations::enemy>> wave_management::get_enemies(unsigned int time) {
            auto return_list = std::vector<std::shared_ptr<domain::nations::enemy>>();

            return return_list;
        }
    }
}