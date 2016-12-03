//
// Created by te on 14-Nov-16.
//

#include "road.h"

namespace domain {
    namespace map {
        namespace objects {

            road::road(engine::math::box2_t box) : dragable_field_object(box) {}

            road::road(std::shared_ptr<field> field1) : dragable_field_object(field1) {}

            /**
             * Copy constructor
             */
            road::road(const road &obj) : dragable_field_object(obj) {
            }

            dragable_field_object *road::clone() const {
                return new road(*this);
            }

            void road::update_game_stats(domain::game_level::game_stats &game_stats1) {
                game_stats1.increase("roads");
            }
        }
    }
}
