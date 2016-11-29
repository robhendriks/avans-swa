//
// Created by robbie on 17-11-2016.
//

#ifndef CITY_DEFENCE_DROPABLE_H
#define CITY_DEFENCE_DROPABLE_H


#include "../math/box2.hpp"
#include "dragable.h"
#include "drag_and_drop.h"

namespace engine {
    namespace draganddrop {
        class drag_and_drop;
    }
}

namespace engine {
    namespace draganddrop {
        class dragable;
    }
}

namespace engine {
    namespace draganddrop {
        class dropable {
        public:
            virtual math::box2_t get_box() const = 0;

            virtual bool drop(dragable *dragable1) = 0;

            void set_drag_and_drop(drag_and_drop *drag_and_drop1);

            virtual ~dropable() = default;

        protected:
            drag_and_drop *m_drag_and_drop;
        };
    }
}


#endif //CITY_DEFENCE_DROPABLE_H
