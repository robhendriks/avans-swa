//
// Created by robbie on 6-11-2016.
//

#ifndef CITY_DEFENCE_OBJECT_CANNOT_BE_PLACED_ON_FIELD_H
#define CITY_DEFENCE_OBJECT_CANNOT_BE_PLACED_ON_FIELD_H


#include "../domain/map/objects/dragable_field_object.h"

namespace events {
    class object_not_dropped_on_field {
    public:
        object_not_dropped_on_field(domain::map::objects::dragable_field_object &object);
        domain::map::objects::dragable_field_object &get_object() const;

    private:
        domain::map::objects::dragable_field_object &m_object;
    };
}


#endif //CITY_DEFENCE_OBJECT_CANNOT_BE_PLACED_ON_FIELD_H
