//
// Created by robbie on 4-11-2016.
//

#ifndef CITY_DEFENCE_BASE_VIEW_H
#define CITY_DEFENCE_BASE_VIEW_H

#include "../../engine/eventbus/eventbus.h"
#include "../../engine/events/window_cleared.h"
#include "../../engine/math/box2.hpp"

namespace gui {
    namespace views {
        class base_view {
        public:
            /**
             * Called before the first draw of the view
             */
            virtual void before() = 0;

            /**
             * Called after the first draw of the view
             */
            virtual void after() = 0;

            /**
             * Called whenever the view should be drawn
             *
             * @param time_elapsed
             * @param display_box
             */
            virtual void draw(unsigned int time_elapsed, engine::math::box2_t display_box) = 0;

            /**
             * Called when the display box (screen) changes.
             *
             * NOTE: Will always be called after the before() call
             *
             * @param display_box
             */
            virtual void on_display_change(engine::math::box2_t display_box) {};
        };
    }
}


#endif //CITY_DEFENCE_BASE_VIEW_H
