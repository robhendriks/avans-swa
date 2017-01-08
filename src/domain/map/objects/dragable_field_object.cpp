//
// Created by robbie on 19-11-2016.
//

#include "dragable_field_object.h"
#include "../../../events/object_not_dropped_on_field.h"
#include "../../../events/object_dropped_on_field.h"

namespace domain {
    namespace map {
        namespace objects {

            dragable_field_object::dragable_field_object(engine::math::box2_t box) : m_start_box(new engine::math::box2_t(box)),
                                                       m_draw_box(new engine::math::box2_t(box)) {

            }

            dragable_field_object::dragable_field_object(field &field1) : m_start_box(nullptr), m_draw_box(nullptr) {
                set_field(&field1);
            }

            /**
             * Copy constructor
             *
             * @param obj
             */
            dragable_field_object::dragable_field_object(const dragable_field_object &obj) : field_object(obj) {
                m_start_box.reset(new engine::math::box2_t(*obj.m_start_box));
                m_draw_box.reset(new engine::math::box2_t(*obj.m_start_box));
            }

            void dragable_field_object::set_box(engine::math::box2_t box) {
                m_start_box.reset(new engine::math::box2_t(box));
                m_draw_box.reset(new engine::math::box2_t(box));
            }

            engine::math::box2_t dragable_field_object::get_box() const {
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
            void dragable_field_object::on_drag(engine::math::vec2_t position) {
                // Draw on the mouse position
                m_draw_box.reset(new engine::math::box2_t(m_draw_box->width(), m_draw_box->height(), position));
            }

            void dragable_field_object::on_drop(engine::draganddrop::dropable *dropable1) {
                // Remove this as dragable
                m_drag_and_drop->remove_dragable(this);

                // Fire event
                auto *event = new events::object_dropped_on_field(*this);
                engine::eventbus::eventbus::get_instance().fire(*event);
                delete event;
            }

            void dragable_field_object::not_dropped() {
                // Return to start position
                m_draw_box.reset(new engine::math::box2_t(*m_start_box));

                // Fire event
                auto *event = new events::object_not_dropped_on_field(*this);
                engine::eventbus::eventbus::get_instance().fire(*event);
                delete event;
            }

            bool dragable_field_object::can_place_on(field &field1) const {
                return true;
            }
        }
    }
}
