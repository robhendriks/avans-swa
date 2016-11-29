//
// Created by te on 14-Nov-16.
//

#include "road.h"

namespace domain {
    namespace map {
        namespace objects {

            road::road(engine::math::box2_t box, type type1) : dragable_field_object(box), m_type(type1) {}

            road::road(std::shared_ptr<field> field1, type type1) : dragable_field_object(field1), m_type(type1) {}

            void road::on_drop(engine::draganddrop::dropable *dropable1) {
                // Remove this as dragable
                m_drag_and_drop->remove_dragable(this);
            }

            type road::get_type() const {
                return m_type;
            }
        }
    }
}
