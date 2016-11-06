//
// Created by robbie on 6-11-2016.
//

#include "object_cannot_be_placed_on_field.h"

namespace events {

    object_cannot_be_placed_on_field::object_cannot_be_placed_on_field(domain::map::passable_field &field,
                                                   domain::buildings::base_placeable_object &object) : m_field(field),
                                                                                                       m_object(
                                                                                                           object) {

    }

    domain::map::passable_field &object_cannot_be_placed_on_field::get_field() const {
        return m_field;
    }

    domain::buildings::base_placeable_object &object_cannot_be_placed_on_field::get_object() const {
        return m_object;
    }
}
