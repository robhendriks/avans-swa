#ifndef CITY_DEFENCE_BASE_FIELD_H
#define CITY_DEFENCE_BASE_FIELD_H

#include "../../engine/graphics/texture_manager.h"
#include "../buildings/base_placeable_object.h"

namespace domain {
    namespace map {
        class base_field : public domain::drawable::drawable_game_object {
        public:
            base_field(const std::string &id, const std::string &file_loc, engine::math::vec2_t *image_start_position);
            virtual void place(buildings::base_placeable_object* placeable_object) = 0;
            virtual ~base_field() = default;
        };
    }
}
#endif //CITY_DEFENCE_BASE_FIELD_H
