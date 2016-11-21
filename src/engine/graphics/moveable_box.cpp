//
// Created by robbie on 15-11-2016.
//

#include "moveable_box.h"

namespace engine {
    namespace graphics {

        /**
         *
         * @param start_time - in ms
         * @param display_box - box where the movement is taken place
         * @param move_boxes - boxes to move in order of y and then x!
         * @param loops - number of loops, use -1 for infinite
         * @param speed - vector of movement per ms
         * @return
         */
        moveable_box::moveable_box(math::box2_t display_box,
                                   std::vector<math::box2_t> move_boxes, math::vec2_t speed, int loops,
                                   math::vec2_t *restart_center) :
            m_display_box(display_box), m_move_boxes(move_boxes), m_speed(speed), m_loops(loops), m_prev_time(0),
            m_restart_center(restart_center) {

            m_loops_map = new std::map<int, int>();
            for (size_t i = 0; i != m_move_boxes.size(); i++) {
                (*m_loops_map)[i] = 0;
            }

            if (m_restart_center == nullptr) {
                // Use the default restart center calculation
                if (m_move_boxes.size() > 1) {
                    math::vec2_t *center;
                    if (m_speed.y < 0 || (m_speed.y == 0 && m_speed.x < 0)) {
                        center = new math::vec2_t(m_move_boxes[m_move_boxes.size() - 1].center());
                    } else {
                        center = new math::vec2_t(m_move_boxes[0].center());
                    }

                    m_restart_center = center;
                }
            }
        }

        void moveable_box::move(unsigned int time) {
            if (m_prev_time != 0) {
                unsigned int time_diff = time - m_prev_time;
                math::vec2_t move_vec = m_speed;
                move_vec *= time_diff;

                // Move the boxes with the speed
                for (size_t i = 0; i != m_move_boxes.size(); i++) {
                    auto &box = m_move_boxes[i];
                    bool is_in_display = m_display_box.intersects(box);

                    box.add(move_vec);

                    if (is_in_display && ((*m_loops_map)[i] < m_loops || m_loops == -1)) {
                        // Check if the box is still in the display box
                        if (!m_display_box.intersects(box)) {
                            (*m_loops_map)[i]++;
                            if ((*m_loops_map)[i] < m_loops || m_loops == -1) {
                                // Reset the box if there is another loop coming
                                box = math::box2_t(box.width(), box.height(), *m_restart_center);
                            }
                        }
                    }
                }
            }

            m_prev_time = time;
        }

        const std::vector<math::box2_t> &moveable_box::get_boxes() const {
            return m_move_boxes;
        }

        moveable_box::~moveable_box() {
            delete m_restart_center;
            delete m_loops_map;
        }
    }
}
