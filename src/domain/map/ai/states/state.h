//
// Created by te on 08-Dec-16.
//

#ifndef CITY_DEFENCE_STATE_H
#define CITY_DEFENCE_STATE_H


#include <memory>

namespace domain {
    namespace map {
        namespace ai {
            class ai;
            namespace states {
                class state {
                public:

                    virtual void update(ai *ai, unsigned int elapsed_time) = 0;

                    virtual ~state() = default;
                };
            }
        }
    }
}


#endif //CITY_DEFENCE_STATE_H
