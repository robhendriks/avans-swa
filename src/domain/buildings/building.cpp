#ifndef CITY_DEFENCE_BUILDING_CPP
#define CITY_DEFENCE_BUILDING_CPP

#include "building.h"

namespace domain {
    namespace buildings {

        building::building(const std::string &id, const std::string &file_loc,
                           engine::math::vec2_t *image_start_position) : base_placeable_object(id, file_loc,
                                                                                               image_start_position) {}
    }
}

#endif //CITY_DEFENCE_BUILDING_CPP
