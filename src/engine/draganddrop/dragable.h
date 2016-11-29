//
// Created by robbie on 17-11-2016.
//

#ifndef CITY_DEFENCE_DRAGABLE_H
#define CITY_DEFENCE_DRAGABLE_H

#include "dropable.h"
#include "../math/vec2.hpp"
#include "../math/box2.hpp"

namespace engine {
    namespace draganddrop {
        class drag_and_drop;
    }
}

namespace engine {
    namespace draganddrop {
        class dropable;
    }
}

namespace engine {
    namespace draganddrop {
        class dragable {
        public:
            virtual math::box2_t get_box() const = 0;

            virtual void on_drag(math::vec2_t position) = 0;

            virtual void on_drop(dropable *dropable1) = 0;

            virtual void not_dropped() = 0;

            void set_drag_and_drop(drag_and_drop *drag_and_drop1);

            virtual ~dragable() = default;

        protected:
            drag_and_drop *m_drag_and_drop;
        };
    }
}


#endif //CITY_DEFENCE_DRAGABLE_H
