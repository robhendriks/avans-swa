#ifndef CITY_DEFENCE_BUILDING_H
#define CITY_DEFENCE_BUILDING_H

#include <string>
#include "../../../engine/draganddrop/dragable.h"
#include "dragable_field_object.h"
#include "../field.h"
#include "../../game_level/game_stats_modifier.h"

namespace domain {
    namespace map {
        namespace objects {
            class building : public dragable_field_object {
            public:

                building(engine::math::box2_t box);

                building(std::shared_ptr<field> field1);

                building(const building &obj);

                dragable_field_object *clone() const;

                bool can_place_on(field &field1) const;

                void update_game_stats(domain::game_level::game_stats &game_stats1);
            };
        }
    }
}

#endif //CITY_DEFENCE_BUILDING_H
