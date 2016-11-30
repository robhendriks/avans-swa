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

        box_builder &box_builder::center_vertical_in(float height) {
            if (height > m_box.height()) {
                add_margin({0, (height - m_box.height()) / 2});
            }

            return *this;
        }

        box_builder &box_builder::center_horizontal_in(float width) {
            if (width > m_box.width()) {
                add_margin({(width - m_box.width()) / 2, 0});
            }

            return *this;
        }

        math::box2_t box_builder::build() {
            return m_box;
        }
    }
}
