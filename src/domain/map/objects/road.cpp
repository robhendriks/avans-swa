//
// Created by te on 14-Nov-16.
//

#include "road.h"

namespace domain {
    namespace map {
        namespace objects {

            road::road(engine::math::box2_t box) : dragable_field_object(box) {}

            road::road(field &field1) : dragable_field_object(field1) {}

            /**
             * Copy constructor
             */
            road::road(const road &obj) : drawable::drawable_game_object(obj), dragable_field_object(obj) {
            }

            dragable_field_object *road::clone() const {
                return new road(*this);
            }

            void road::update_game_stats(domain::game_level::game_stats &game_stats1, std::string action) {
                if (action == "object-placed") {
                    game_stats1.increase("roads");
                } else if (action == "object-destroyed") {
                    game_stats1.decrease("roads");
                }
            }
        }
    }
}
