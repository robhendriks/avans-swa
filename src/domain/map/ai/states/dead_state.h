//
// Created by te on 08-Dec-16.
//

#ifndef CITY_DEFENCE_DEAD_STATE_H
#define CITY_DEFENCE_DEAD_STATE_H

#include "state.h"

namespace domain {
    namespace map {
        namespace ai {
            namespace states {

                class dead_state : public state {
                public:
                    dead_state() = default;

                    void update(ai *ai, unsigned int elapsed_time);
                };

            }
        }
    }
}

#endif //CITY_DEFENCE_DEAD_STATE_H
