//
// Created by robbie on 6-11-2016.
//

#include "object_placed_on_field.h"

namespace events {

    object_placed_on_field::object_placed_on_field(domain::map::field &field, domain::map::objects::field_object &object) :
            m_field(field), m_object(object) {

    }

    domain::map::field &object_placed_on_field::get_field() const {
        return m_field;
    }

    domain::map::objects::field_object &object_placed_on_field::get_object() const {
        return m_object;
    }
}
