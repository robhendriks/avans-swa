//
// Created by te on 25-Oct-16.
//
#ifndef CITY_DEFENCE_BASE_PLACEABLE_OBJECT_CPP
#define CITY_DEFENCE_BASE_PLACEABLE_OBJECT_CPP

#include "base_placeable_object.h"

namespace domain {
    namespace buildings {
        base_placeable_object::base_placeable_object(const std::string &id, const std::string &file_loc,
                                                     engine::math::vec2_t *image_start_position, int rotation) : drawable_game_object(
                id, file_loc, image_start_position, rotation) {}
    }
}

#endif //CITY_DEFENCE_BASE_PLACEABLE_OBJECT_CPP
