#ifndef CITY_DEFENCE_BASE_PLACEABLE_OBJECT_HPP
#define CITY_DEFENCE_BASE_PLACEABLE_OBJECT_HPP

#include "passable_field.h"
#include "../../engine/eventbus/eventbus.h"
#include "../../events/object_placed_on_field.h"
#include "../../events/object_cannot_be_placed_on_field.h"

namespace domain {
    namespace map {
        passable_field::passable_field(const std::string &id, const std::string &file_loc,
                                       engine::math::vec2_t *image_start_position, int rotation, int x, int y) : base_field(id, file_loc, image_start_position, rotation, x, y) {
            m_placed_object = nullptr;
        }

        void passable_field::draw(engine::graphics::texture_manager &texture_manager, engine::math::box2_t &dest) {
            if (m_placed_object == nullptr) {
                base_field::draw(texture_manager, dest);
            } else {
                m_placed_object->draw(texture_manager, dest);
            }
        }

        void passable_field::place(buildings::base_placeable_object* placeable_object) {
            if (m_placed_object == nullptr) {
                m_placed_object = placeable_object;
                // Fire event
                auto *event = new events::object_placed_on_field(*this, *placeable_object);
                engine::eventbus::eventbus::get_instance().fire(*event);
                delete event;

                // notify local observers
                this->notify_observers(this);
            } else {
                // Fire event
                auto *event = new events::object_cannot_be_placed_on_field(*this, *placeable_object);
                engine::eventbus::eventbus::get_instance().fire(*event);
                delete event;
            }
        }

        void passable_field::unload(engine::graphics::texture_manager &texture_manager) {
            base_field::unload(texture_manager);
            if(m_placed_object != nullptr)
                m_placed_object->unload(texture_manager);
        }

        passable_field::~passable_field() {
            if(m_placed_object != nullptr){
                delete m_placed_object;
                m_placed_object = nullptr;
            }
        }

        buildings::base_placeable_object *passable_field::get_placed_object() {
            return this->m_placed_object;
        }
    }
}

#endif //CITY_DEFENCE_BASE_PLACEABLE_OBJECT_HPP
