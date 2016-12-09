#ifndef CITY_DEFENCE_BASE_FIELD_CPP
#define CITY_DEFENCE_BASE_FIELD_CPP

#include "field.h"
#include "../../events/object_dropped_on_field.h"
#include "../../events/object_not_dropped_on_field.h"
#include "objects/dragable_field_object.h"
#include "../../engine/graphics/font_manager.h"

namespace domain {
    namespace map {

        field::field(engine::math::vec2_t pos)
            : m_pos(pos), m_object(nullptr), m_box(nullptr) {}

        field::~field() {
        }

        /**
         * Draw a field and the object that is placed
         *
         * @param texture_manager
         */
        void field::draw(drawable::draw_managers_wrapper &draw_managers, unsigned int time_elapsed) {
            drawable::drawable_game_object::draw(draw_managers, time_elapsed);

            if (m_object) {
                // Let the object draw
                m_object->draw(draw_managers, time_elapsed);
            }

            // Printing the weight on the fields
            draw_managers.texture_manager.load_text(std::to_string(m_weight), {254, 12, 10},
                                                    *draw_managers.font_manager.get_font("roboto", 32),
                                                    "heatmap_weight");
            draw_managers.texture_manager.draw("heatmap_weight", {0, 0}, this->get_box());
            draw_managers.texture_manager.unload("heatmap_weight");
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
            auto *object = dynamic_cast<objects::dragable_field_object *>(dragable1);
            if (object && object->can_place_on(*this)) {
                if (place_object(object)) {
                    // Remove this as dropable
                    m_drag_and_drop->remove_dropable(this);

                    object->set_max_column(2);
                }

                return true;
            }

            return false;
        }

        /**
         * Update the screen box of the field
         *
         * @param box
         */
        void field::set_box(std::shared_ptr<engine::math::box2_t> box) {
            m_box = box;
        }

        /**
         * Place an object on the field
         *
         * @param object
         */
        bool field::place_object(objects::field_object *object) {
            if (!has_object()) {
                m_object = object;
                m_object->set_field(std::shared_ptr<field>(this));
                m_object->add_observer(this);

                // notify local observers
                notify_observers(this, "object-placed");

                return true;
            }

            return false;
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
            return m_map->get_neighbors(get_position());
        }

        /**
         * Get the position/coördinates of the field on the map
         *
         * @return engine::math::vec2_t
         */
        engine::math::vec2_t field::get_position() const {
            return m_pos;
        }

        long field::get_weight() const {
            return m_weight;
        }

        void field::set_weight(long weight) {
            m_weight = weight;
        }

        void field::notify(objects::field_object *p_observee, std::string title) {
            if (title == "object-destroyed") {
                // it can be that a object still is linked to this field but still needs to be removed even
                // if it is already removed from the field itself
                if (m_object != nullptr) {
                    notify_observers(this, title);
                    m_object = nullptr;
                    m_drag_and_drop->add_dropable(*this);
                }
            }
        }

        std::shared_ptr<map> field::get_map() const {
            return m_map;
        }

        void field::set_map(const std::shared_ptr<map> &map) {
            m_map = map;
        }

    }
}

#endif //CITY_DEFENCE_BASE_FIELD_CPP
