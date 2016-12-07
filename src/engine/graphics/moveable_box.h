//
// Created by robbie on 15-11-2016.
//

#ifndef CITY_DEFENCE_MOVEABLE_BOX_H
#define CITY_DEFENCE_MOVEABLE_BOX_H

#include <vector>
#include <map>
#include "../math/box2.hpp"

namespace engine {
    namespace graphics {
        class moveable_box {
        public:
            moveable_box(math::box2_t display_box, std::vector<math::box2_t> move_boxes, math::vec2_t speed,
                         int loops = 1, math::vec2_t *restart_center = nullptr);

            ~moveable_box();

            void move(unsigned int time);

            const std::vector<math::box2_t> &get_boxes() const;

            void change_speed(math::vec2_t speed);

        private:
            math::box2_t m_display_box;
            std::vector<math::box2_t> m_move_boxes;
            std::map<int, int> *m_loops_map;
            math::vec2_t m_speed;
            int m_loops;
            unsigned int m_prev_time;
            math::vec2_t *m_restart_center;
        };
    }
}

#endif //CITY_DEFENCE_MOVEABLE_BOX_H
