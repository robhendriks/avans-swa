#ifndef CITY_DEFENCE_BUILDING_H
#define CITY_DEFENCE_BUILDING_H

#include <string>
#include "../../../engine/draganddrop/dragable.h"
#include "object.h"
#include "../field.h"

namespace domain {
    namespace map {
        namespace objects {
            class building : public object {
            public:

                building(engine::math::box2_t box);

                building(domain::map::field *field1);

                bool can_place_on(field &field1) const;

                void on_drop(engine::draganddrop::dropable *dropable1);
            };
        }
    }
}

#endif //CITY_DEFENCE_BUILDING_H
