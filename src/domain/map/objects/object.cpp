//
// Created by robbie on 19-11-2016.
//

#include "object.h"

namespace domain {
    namespace map {
        namespace objects {

            object::object(engine::math::box2_t box) : m_start_box(new engine::math::box2_t(box)),
                                                       m_draw_box(new engine::math::box2_t(box)), m_field(nullptr) {

            }

            object::object(domain::map::field *field1) : m_start_box(nullptr), m_draw_box(nullptr), m_field(field1) {

            }

            engine::math::box2_t object::get_box() const {
                if (m_field) {
                    return m_field->get_box();
                }

                return *m_draw_box;
            }

            /**
             * This function will only be called when the object has no field
             *
             * @param position
             */
            void object::on_drag(engine::math::vec2_t position) {
                // Draw on the mouse position
                auto temp_box = engine::math::box2_t(*m_draw_box);
                delete m_draw_box;
                m_draw_box = new engine::math::box2_t(temp_box.width(), temp_box.height(), position);
            }

            void object::not_dropped() {
                // Return to start position
                delete m_draw_box;
                m_draw_box = new engine::math::box2_t(*m_start_box);
            }

            bool object::can_place_on(field &field1) const {
                return true;
            }

            void object::set_field(field *field1) {
                m_field = field1;
            }

            object::~object() {
                if (m_start_box) {
                    delete m_start_box;
                }

                if (m_draw_box) {
                    delete m_draw_box;
                }
            }
        }
    }
}
