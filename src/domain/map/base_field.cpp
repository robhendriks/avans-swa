#ifndef CITY_DEFENCE_BASE_FIELD_CPP
#define CITY_DEFENCE_BASE_FIELD_CPP
#include "base_field.h"


namespace domain {
    namespace map {
        base_field::base_field(const std::string &id, const std::string &file_loc,
                               engine::math::vec2_t *image_start_position, int x, int y, int rotation) : drawable_game_object(id, file_loc,
                                                                                                  image_start_position, rotation) , m_x(x), m_y(y){}

        int base_field::get_x() {
            return m_x;
        }

        int base_field::get_y() {
            return m_y;
        }
    }
}

#endif //CITY_DEFENCE_BASE_FIELD_CPP
