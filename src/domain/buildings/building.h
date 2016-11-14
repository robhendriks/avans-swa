#ifndef CITY_DEFENCE_BUILDING_H
#define CITY_DEFENCE_BUILDING_H

#include "base_placeable_object.h"

namespace domain {
    namespace buildings{
        class building : public base_placeable_object {
        public:
            building(const std::string &id, const std::string &file_loc, engine::math::vec2_t *image_start_position, int rotation);
        };
    }
}
#endif //CITY_DEFENCE_BUILDING_H
