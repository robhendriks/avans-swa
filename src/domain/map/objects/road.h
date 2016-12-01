//
// Created by te on 14-Nov-16.
//

#ifndef CITY_DEFENCE_ROAD_H
#define CITY_DEFENCE_ROAD_H

#include <string>
#include "../../../engine/draganddrop/dragable.h"
#include "dragable_field_object.h"

namespace domain {
    namespace map {
        namespace objects {
            class road : public dragable_field_object {
            public:

                road(engine::math::box2_t box);

                road(std::shared_ptr<field> field1);

                road(const road &obj);

                dragable_field_object *clone() const;
            };
        }
    }
}


#endif //CITY_DEFENCE_ROAD_H
