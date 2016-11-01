#ifndef CITY_DEFENCE_PASSABLE_FIELD_H
#define CITY_DEFENCE_PASSABLE_FIELD_H

#include "../buildings/base_placeable_object.h"

namespace domain {
    namespace map {
        class passable_field {
        public:
            passable_field();
            void set_placed_object(buildings::base_placeable_object placeable_object);
            buildings::base_placeable_object get_placed_object();
            ~passable_field();

        private:
            buildings::base_placeable_object _placed_object;
        };
    }
}
#endif //CITY_DEFENCE_PASSABLE_FIELD_H
