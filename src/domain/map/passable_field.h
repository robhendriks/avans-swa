#ifndef CITY_DEFENCE_PASSABLE_FIELD_H
#define CITY_DEFENCE_PASSABLE_FIELD_H

#include "../buildings/base_placeable_object.h"
#include "base_field.h"

namespace domain {
    namespace map {
        class passable_field : public base_field {
        public:
            void draw(engine::graphics::texture_manager &texture_manager, engine::math::box2_t &dest);
            void place(buildings::base_placeable_object &placeable_object);
            buildings::base_placeable_object &get_placed_object();
        private:
            buildings::base_placeable_object *m_placed_object;
        };
    }
}
#endif //CITY_DEFENCE_PASSABLE_FIELD_H
