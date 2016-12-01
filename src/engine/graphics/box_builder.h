//
// Created by robbie on 30-11-2016.
//

#ifndef CITY_DEFENCE_BOX_FACTORY_H
#define CITY_DEFENCE_BOX_FACTORY_H

#include "../math/box2.hpp"

namespace engine {
    namespace graphics {
        class box_builder {
        public:
            box_builder(const math::vec2_t &box_size);

            box_builder &add_margin(const math::vec2_t &margin);

            box_builder &to_center(const math::box2_t &box);

            box_builder &as_center(const math::vec2_t &vec);

            box_builder &as_left_top(const math::vec2_t &vec);

            box_builder &as_right_top(const math::vec2_t &vec);

            box_builder &as_left_bottom(const math::vec2_t &vec);

            box_builder &as_right_bottom(const math::vec2_t &vec);

            box_builder &center_vertical(float y1, float y2);

            box_builder &center_horizontal(float x1, float x2);

            box_builder &start_on_y(float y);

            box_builder &start_on_x(float x);

            math::box2_t build();

        private:
            math::box2_t m_box;
        };
    }
}


#endif //CITY_DEFENCE_BOX_FACTORY_H
