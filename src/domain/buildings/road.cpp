//
// Created by te on 14-Nov-16.
//

#include "road.h"
namespace domain {
    namespace buildings {
        road::road(const std::string &id, const std::string &file_loc, engine::math::vec2_t *image_start_position, int rotation)
                : base_placeable_object(id, file_loc, image_start_position, rotation) {}
    }
}