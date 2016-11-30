#ifndef CITY_DEFENCE_BUILDING_H
#define CITY_DEFENCE_BUILDING_H

#include <string>
#include "../../../engine/draganddrop/dragable.h"
#include "dragable_field_object.h"
#include "../field.h"

namespace domain {
    namespace map {
        namespace objects {
            class building : public dragable_field_object {
            public:

                building(engine::math::box2_t box);

                building(std::shared_ptr<field> field1);

                bool can_place_on(field &field1) const;
            };
        }
    }
}

#endif //CITY_DEFENCE_BUILDING_H
