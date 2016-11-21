#ifndef CITY_DEFENCE_BASE_FIELD_H
#define CITY_DEFENCE_BASE_FIELD_H

#include "../../engine/graphics/texture_manager.h"
#include "../buildings/base_placeable_object.h"
#include "../../engine/observer/observee.h"

namespace domain {
    namespace map {
        class base_field : public domain::drawable::drawable_game_object, public engine::observer::observee<base_field> {
        public:
            //const std::string &file_loc, engine::math::vec2_t *image_start_position,  ?? dit moet in een sprite class
            base_field(const std::string &id, const std::string &file_loc, engine::math::vec2_t *image_start_position, int x, int y, int rotation = 0);
            virtual void place(buildings::base_placeable_object* placeable_object) = 0;
            virtual ~base_field() = default;
            int get_x();
            int get_y();
            virtual buildings::base_placeable_object* get_placed_object() = 0;
        private:
            int m_x;
            int m_y;
        };
    }
}
#endif //CITY_DEFENCE_BASE_FIELD_H
