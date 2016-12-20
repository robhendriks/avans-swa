//
// Created by robbie on 29-11-2016.
//

#include "field_object.h"

namespace domain {
    namespace map {
        namespace objects {

            field_object::field_object() : m_rotation(0), m_field(nullptr) {}

            /**
             * Copy constructor
             *
             * @param obj
             */
            field_object::field_object(const field_object &obj) {
                m_rotation = obj.get_rotation();
                m_field = nullptr;
            }

            void field_object::set_rotation(int rotation) {
                m_rotation = rotation;
            }

            int field_object::get_rotation() const {
                return m_rotation;
            }

            void field_object::set_field(std::shared_ptr<field> field1) {
                m_field = field1;
            }

            std::shared_ptr<field> field_object::get_field() const {
                return m_field;
            }
        }
    }
}
