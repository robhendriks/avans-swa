//
// Created by robbie on 30-11-2016.
//

#include "box_builder.h"

namespace engine {
    namespace graphics {

        box_builder::box_builder(const math::vec2_t &box_size) : m_box({0, 0}, box_size) {}

        box_builder &box_builder::add_margin(const math::vec2_t &margin) {
            m_box.add(margin);

            return *this;
        }

        box_builder &box_builder::to_center(const math::box2_t &box) {
            as_center(box.center());

            return *this;
        }

        box_builder &box_builder::as_center(const math::vec2_t &vec) {
            m_box = engine::math::box2_t(m_box.width(), m_box.height(), vec);

            return *this;
        }

        box_builder &box_builder::as_left_top(const math::vec2_t &vec) {
            m_box = engine::math::box2_t(vec, vec + m_box.size());

            return *this;
        }

        box_builder &box_builder::as_right_top(const math::vec2_t &vec) {
            m_box = engine::math::box2_t(vec - math::vec2_t({m_box.width(), 0}), vec + math::vec2_t({0, m_box.height()}));

            return *this;
        }

        box_builder &box_builder::as_left_bottom(const math::vec2_t &vec) {
            m_box = engine::math::box2_t(vec - math::vec2_t({0, m_box.height()}), vec + math::vec2_t({m_box.width(), 0}));

            return *this;
        }

        box_builder &box_builder::as_right_bottom(const math::vec2_t &vec) {
            m_box = engine::math::box2_t(vec - m_box.size(), vec);

            return *this;
        }

        box_builder &box_builder::center_vertical(float y1, float y2) {
            if (y1 > y2) {
                std::swap(y1, y2);
            }

            auto center = m_box.center();
            center.y = y1 + ((y2 - y1) / 2);

            m_box = engine::math::box2_t(m_box.width(), m_box.height(), center);

            return *this;
        }

        box_builder &box_builder::center_horizontal(float x1, float x2) {
            if (x1 > x2) {
                std::swap(x1, x2);
            }

            auto center = m_box.center();
            center.x = x1 + ((x2 - x1) / 2);

            m_box = engine::math::box2_t(m_box.width(), m_box.height(), center);

            return *this;
        }

        box_builder &box_builder::start_on_y(float y) {
            float h = m_box.height();
            m_box.min.y = y;
            m_box.max.y = y + h;

            return *this;
        }

        box_builder &box_builder::start_on_x(float x) {
            float w = m_box.width();
            m_box.min.x = x;
            m_box.max.x = x + w;

            return *this;
        }

        math::box2_t box_builder::build() {
            return m_box;
        }
    }
}
