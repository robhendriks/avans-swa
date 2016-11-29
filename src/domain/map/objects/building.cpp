#ifndef CITY_DEFENCE_BUILDING_CPP
#define CITY_DEFENCE_BUILDING_CPP

#include "building.h"
#include "road.h"

namespace domain {
    namespace map {
        namespace objects {

            building::building(engine::math::box2_t box) : dragable_field_object(box) {}

            building::building(std::shared_ptr<field> field1) : dragable_field_object(field1) {}

            /**
             * Called when the building is successfully dropped/placed on a field
             *
             * @param dropable1
             */
            void building::on_drop(engine::draganddrop::dropable *dropable1) {
                m_drag_and_drop->remove_dragable(this);
//                auto *field1 = dynamic_cast<field*>(dropable1);
//                if (field1) {
//                    set_field(field1);
//                }

            }

            /**
             * Make sure a building can only be placed next to a road object
             *
             * @param field1
             * @return
             */
            bool building::can_place_on(field &field1) const {
                for (auto &neighbor : field1.get_neighbors()) {
                    if (neighbor->has_object() && dynamic_cast<road*>(neighbor->get_object())) {
                        return true;
                    }
                }

                return false;
            }
        }
    }
}

#endif //CITY_DEFENCE_BUILDING_CPP
