//
// Created by robbie on 30-11-2016.
//

#include "box_builder.h"

namespace engine {
    namespace graphics {

        /**
         * Create a new box builder
         *
         * @param box_size - the size of the box that should be created
         */
        box_builder::box_builder(const math::vec2_t &box_size) : m_box({0, 0}, box_size) {}

        box_builder &box_builder::add_margin(const math::vec2_t &margin) {
            m_box.add(margin);

            return *this;
        }

        /**
         * Position the new box in the center of another box
         *
         * @param box
         * @return
         */
        box_builder &box_builder::to_center(const math::box2_t &box) {
            as_center(box.center());

            return *this;
        }

        /**
         * Set a position as the center of the new box
         *
         * @param vec
         * @return
         */
        box_builder &box_builder::as_center(const math::vec2_t &vec) {
            m_box = engine::math::box2_t(m_box.width(), m_box.height(), vec);

            return *this;
        }

        /**
         * Set a position as the left top of the new box
         *
         * @param vec
         * @return
         */
        box_builder &box_builder::as_left_top(const math::vec2_t &vec) {
            m_box = engine::math::box2_t(vec, vec + m_box.size());

            return *this;
        }

        /**
         * Set the position of the right top of the new box
         *
         * @param vec
         * @return
         */
        box_builder &box_builder::as_right_top(const math::vec2_t &vec) {
            m_box = engine::math::box2_t(vec - math::vec2_t({m_box.width(), 0}), vec + math::vec2_t({0, m_box.height()}));

            return *this;
        }

        /**
         * Set the position of the left bottom of the new box
         *
         * @param vec
         * @return
         */
        box_builder &box_builder::as_left_bottom(const math::vec2_t &vec) {
            m_box = engine::math::box2_t(vec - math::vec2_t({0, m_box.height()}), vec + math::vec2_t({m_box.width(), 0}));

            return *this;
        }

        /**
         * Set the position of the right bottom of the new box
         *
         * @param vec
         * @return
         */
        box_builder &box_builder::as_right_bottom(const math::vec2_t &vec) {
            m_box = engine::math::box2_t(vec - m_box.size(), vec);

            return *this;
        }

        /**
         * Center the new box vertical between two y coordinates
         *
         * @param y1
         * @param y2
         * @return
         */
        box_builder &box_builder::center_vertical(float y1, float y2) {
            if (y1 > y2) {
                std::swap(y1, y2);
            }

            auto center = m_box.center();
            center.y = y1 + ((y2 - y1) / 2);

            m_box = engine::math::box2_t(m_box.width(), m_box.height(), center);

            return *this;
        }

        /**
         * Center the new box horizontal between two x coordinates
         *
         * @param x1
         * @param x2
         * @return
         */
        box_builder &box_builder::center_horizontal(float x1, float x2) {
            if (x1 > x2) {
                std::swap(x1, x2);
            }

            auto center = m_box.center();
            center.x = x1 + ((x2 - x1) / 2);

            m_box = engine::math::box2_t(m_box.width(), m_box.height(), center);

            return *this;
        }

        /**
         * Set/force the min y position of the box
         *
         * @param y
         * @return
         */
        box_builder &box_builder::start_on_y(float y) {
            float h = m_box.height();
            m_box.min.y = y;
            m_box.max.y = y + h;

            return *this;
        }

        /**
         * Set/force the min x position of the box
         *
         * @param x
         * @return
         */
        box_builder &box_builder::start_on_x(float x) {
            float w = m_box.width();
            m_box.min.x = x;
            m_box.max.x = x + w;

            return *this;
        }

        /**
         * Build the final box
         *
         * @return
         */
        math::box2_t box_builder::build() {
            return m_box;
        }

        /**
         * Set box location
         *
         * @return
         */
        void box_builder::set_box(math::box2_t * box) {
            m_box = *box;
        }
    }
}
