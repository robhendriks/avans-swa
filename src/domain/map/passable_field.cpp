#ifndef CITY_DEFENCE_BASE_PLACEABLE_OBJECT_HPP
#define CITY_DEFENCE_BASE_PLACEABLE_OBJECT_HPP
#include "passable_field.h"

namespace domain {
    namespace map {
        void passable_field::draw(engine::graphics::texture_manager &texture_manager, engine::math::box2_t &dest) {
            if (m_placed_object == nullptr) {
                texture_manager.draw("grass_1", {0, 0}, dest);
            } else {
                texture_manager.draw("building_1", {0, 0}, dest);
            }
        }

        buildings::base_placeable_object &passable_field::get_placed_object() {
            return *m_placed_object;
        }

        void passable_field::place(buildings::base_placeable_object &placeable_object) {
            if (m_placed_object == nullptr) {
                m_placed_object = &placeable_object;
            }
            SDL_Log("ALREADY SOMETHING PLACED");
        }
    }
}
#endif //CITY_DEFENCE_BASE_PLACEABLE_OBJECT_HPP
