//
// Created by te on 08-Dec-16.
//

#ifndef CITY_DEFENCE_ATTACK_STATE_H
#define CITY_DEFENCE_ATTACK_STATE_H

#include "ai_state.h"

namespace map {
    namespace ai {
        namespace states {
            class attack_state : public ai_state {
            public:
                void update(ai* ai);
            };
        }
    }
}



#endif //CITY_DEFENCE_ATTACK_STATE_H
