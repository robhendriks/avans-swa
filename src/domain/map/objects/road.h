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
            enum type {
                STRAIGHT, JUNCTION, CORNER, CAP, T_JUNCTION
            };

            class road : public dragable_field_object {
            public:

                road(engine::math::box2_t box, type type1);

                road(std::shared_ptr<field> field1, type type1);

                type get_type() const;

            private:
                type m_type;
            };
        }
    }
}


#endif //CITY_DEFENCE_ROAD_H
