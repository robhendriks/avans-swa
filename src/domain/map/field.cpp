#ifndef CITY_DEFENCE_BASE_FIELD_CPP
#define CITY_DEFENCE_BASE_FIELD_CPP

#include "field.h"
#include "../../events/object_placed_on_field.h"
#include "../../events/object_cannot_be_placed_on_field.h"
#include "objects/dragable_field_object.h"


namespace domain {
    namespace map {

        field::field(map &map1, engine::math::vec2_t pos) : m_map(map1), m_pos(pos), m_object(nullptr), m_box(nullptr) {
            map1.add_field(std::shared_ptr<field>(this));
        }

        field::~field() {
            if (m_box != nullptr) {
                delete m_box;
            }
        }

        /**
         * Draw a field and the object that is placed
         *
         * @param texture_manager
         */
        void field::draw(engine::graphics::texture_manager &texture_manager, unsigned int time_elapsed) {
            drawable::drawable_game_object::draw(texture_manager, time_elapsed);

            if (m_object) {
                // Let the object draw
                m_object->draw(texture_manager, time_elapsed);
            }
        }
        /**
         * Get the box where the field is placed on the screen
         *
         * @return
         */
        engine::math::box2_t field::get_box() const {
            return *m_box;
        }

        /**
         * Called when a dragable (object) is dropped on the field
         *
         * @param dragable1
         * @return bool - whether it is successfully placed or not
         */
        bool field::drop(engine::draganddrop::dragable *dragable1) {
            auto *object = dynamic_cast<objects::dragable_field_object*>(dragable1);
            if (object && object->can_place_on(*this)) {
                // Remove this as dropable
                m_drag_and_drop->remove_dropable(this);

                place_object(*object);

                return true;
            }

            return false;
        }

        /**
         * Update the screen box of the field
         *
         * @param box
         */
        void field::set_box(engine::math::box2_t box) {
            if (m_box != nullptr) {
                delete m_box;
            }

            m_box = new engine::math::box2_t(box);
        }

        /**
         * Place an object on the field
         *
         * @param object
         */
        void field::place_object(objects::field_object &object) {
            if (!has_object()) {
                m_object = &object;
                m_object->set_field(std::shared_ptr<field>(this));

                // Fire event
                auto *event = new events::object_placed_on_field(*this, object);
                engine::eventbus::eventbus::get_instance().fire(*event);
                delete event;

                // notify local observers
                notify_observers(this, "object-placed");
            } else {
                // Fire event
                auto *event = new events::object_cannot_be_placed_on_field(*this, object);
                engine::eventbus::eventbus::get_instance().fire(*event);
                delete event;
            }
        }

        /**
         * @return bool - whether the field has an object or not
         */
        bool field::has_object() const {
            return m_object != nullptr;
        }

        /**
         * @return object* - the object that is placed on this field or a nullptr when nothing is placed
         */
        objects::field_object *field::get_object() const {
            return m_object;
        }

        /**
         * Get the neighbors of the field
         *
         * @return std::vector<field&>
         */
        std::vector<std::shared_ptr<field>> field::get_neighbors() const {
            return m_map.get_neighbors(get_position());
        }

        /**
         * Get the position/coördinates of the field on the map
         *
         * @return engine::math::vec2_t
         */
        engine::math::vec2_t field::get_position() const {
            return m_pos;
        }
    }
}

#endif //CITY_DEFENCE_BASE_FIELD_CPP
