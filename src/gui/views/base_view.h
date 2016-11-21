//
// Created by robbie on 4-11-2016.
//

#ifndef CITY_DEFENCE_BASE_VIEW_H
#define CITY_DEFENCE_BASE_VIEW_H

#include "../../engine/eventbus/eventbus.h"
#include "../../engine/events/window_cleared.h"

namespace gui {
    namespace views {
        class base_view {
        public:
            virtual void before() = 0;
            virtual void after() = 0;
            virtual void draw(float interpolation) = 0;
        };
    }
}


#endif //CITY_DEFENCE_BASE_VIEW_H
