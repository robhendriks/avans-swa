//
// Created by te on 14-Nov-16.
//

#ifndef CITY_DEFENCE_ROAD_H
#define CITY_DEFENCE_ROAD_H

#include "base_placeable_object.h"

namespace domain {
    namespace buildings{
        class road :  public base_placeable_object {
        public:
            road(const std::string &id, const std::string &file_loc, engine::math::vec2_t *image_start_position, int rotation = 0);
        };
    }
}


#endif //CITY_DEFENCE_ROAD_H
