//
// Created by te on 08-Dec-16.
//

#ifndef CITY_DEFENCE_AI_STATE_H
#define CITY_DEFENCE_AI_STATE_H

namespace map {
    namespace ai {
        class ai;
        namespace states {
            class ai_state {
            public:
                virtual void update(ai* ai) = 0;
            };
        }
    }
}

#endif //CITY_DEFENCE_AI_STATE_H
