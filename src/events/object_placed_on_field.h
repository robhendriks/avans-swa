//
// Created by robbie on 6-11-2016.
//

#ifndef CITY_DEFENCE_OBJECT_PLACED_ON_FIELD_H
#define CITY_DEFENCE_OBJECT_PLACED_ON_FIELD_H

#include "../domain/buildings/base_placeable_object.h"
#include "../domain/map/passable_field.h"

namespace events {
    class object_placed_on_field {
    public:
        object_placed_on_field(domain::map::passable_field &field, domain::buildings::base_placeable_object &object);
        domain::map::passable_field &get_field() const;
        domain::buildings::base_placeable_object &get_object() const;

    private:
        domain::map::passable_field &m_field;
        domain::buildings::base_placeable_object &m_object;
    };
}

#endif //CITY_DEFENCE_OBJECT_PLACED_ON_FIELD_H
