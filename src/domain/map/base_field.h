#ifndef CITY_DEFENCE_BASE_FIELD_H
#define CITY_DEFENCE_BASE_FIELD_H

#include "../../engine/graphics/texture_manager.h"
#include "../buildings/base_placeable_object.h"

namespace domain {
    namespace map {
        class base_field {
        public:
            virtual void draw(engine::graphics::texture_manager &texture_manager, engine::math::box2_t &dest) = 0;
            virtual void place(buildings::base_placeable_object &placeable_object) = 0;
            virtual ~base_field() = default;
        };
    }
}
#endif //CITY_DEFENCE_BASE_FIELD_H
