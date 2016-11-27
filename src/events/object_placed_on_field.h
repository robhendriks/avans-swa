//
// Created by robbie on 6-11-2016.
//

#ifndef CITY_DEFENCE_OBJECT_PLACED_ON_FIELD_H
#define CITY_DEFENCE_OBJECT_PLACED_ON_FIELD_H


#include "../domain/map/objects/field_object.h"
#include "../domain/map/field.h"

namespace events {
    class object_placed_on_field {
    public:
        object_placed_on_field(domain::map::field &field, domain::map::objects::field_object &object);
        domain::map::field &get_field() const;
        domain::map::objects::field_object &get_object() const;

    private:
        domain::map::field &m_field;
        domain::map::objects::field_object &m_object;
    };
}

#endif //CITY_DEFENCE_OBJECT_PLACED_ON_FIELD_H
