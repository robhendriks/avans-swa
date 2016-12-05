//
// Created by robbie on 6-11-2016.
//

#include "object_dropped_on_field.h"

namespace events {

    object_dropped_on_field::object_dropped_on_field(domain::map::objects::dragable_field_object &object) :
        m_object(object) {

    }

    domain::map::objects::dragable_field_object &object_dropped_on_field::get_object() const {
        return m_object;
    }
}
