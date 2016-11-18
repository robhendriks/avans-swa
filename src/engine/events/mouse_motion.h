//
// Created by robbie on 17-11-2016.
//

#ifndef CITY_DEFENCE_MOUSE_MOTION_H
#define CITY_DEFENCE_MOUSE_MOTION_H

#include "../math/vec2.hpp"

namespace engine {
    namespace events {
        class mouse_motion {
        public:
            mouse_motion(math::vec2_t mouse_position);
            math::vec2_t get_mouse_position() const;
        private:
            math::vec2_t m_mouse_position;
        };
    }
}


#endif //CITY_DEFENCE_MOUSE_MOTION_H
