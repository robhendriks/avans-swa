//
// Created by te on 08-Dec-16.
//

#ifndef CITY_DEFENCE_ATTACK_STATE_H
#define CITY_DEFENCE_ATTACK_STATE_H

#include "state.h"
#include "../../objects/field_object.h"
#include "../../../combat/defender.h"

namespace domain {
    namespace map {
        namespace ai {
            namespace states {
                class search_and_destroy_state : public state {
                public:
                    search_and_destroy_state();
                    void update(ai * ai, unsigned int elapsed_time);
                private:
                    domain::combat::defender* m_current_target;
                    int m_last_attack_time = 0;
                };
            }
        }
    }
}

#endif //CITY_DEFENCE_ATTACK_STATE_H
