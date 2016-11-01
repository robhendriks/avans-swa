#ifndef CITY_DEFENCE_BASE_PLACEABLE_OBJECT_HPP
#define CITY_DEFENCE_BASE_PLACEABLE_OBJECT_HPP
#include "passable_field.h"

namespace domain {
    namespace map {
        passable_field::passable_field() {
        }


        passable_field::~passable_field() {
        }

        void passable_field::set_placed_object(buildings::base_placeable_object placeable_object) {
            this->_placed_object = placeable_object;
        }

        buildings::base_placeable_object passable_field::get_placed_object() {
            return buildings::base_placeable_object();
        }
    }
}
#endif //CITY_DEFENCE_BASE_PLACEABLE_OBJECT_HPP
