#ifndef CITY_DEFENCE_BASE_FIELD_CPP
#define CITY_DEFENCE_BASE_FIELD_CPP

#include "field.h"
#include "../../events/object_dropped_on_field.h"
#include "../../events/object_not_dropped_on_field.h"
#include "objects/dragable_field_object.h"
#include "../../engine/graphics/font_manager.h"
#include "objects/defensive_building.h"
#include "ai/states/search_and_destroy_state.h"

namespace domain {
    namespace map {

        field::field(map &map1, engine::math::vec2_t pos) : m_map(map1), m_pos(pos), m_object(nullptr), m_box(nullptr), m_flags(FLAG_NONE) {
            map1.add_field(std::shared_ptr<field>(this));
        }

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

            if ((m_flags & FLAG_WEIGHT) != 0) {
                // Printing the weight on the fields
                draw_managers.texture_manager.load_text(std::to_string(m_weight), {254, 12, 10},
                                                        *draw_managers.font_manager.get_font("roboto", 32),
                                                        "heatmap_weight");
                draw_managers.texture_manager.draw("heatmap_weight", {0, 0}, get_box());
                draw_managers.texture_manager.unload("heatmap_weight");
            }

            if ((m_flags & FLAG_TARGET) != 0) {
                draw_managers.color_manager.stroke({255, 0, 0}, get_box());
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
                if (place_object(object)) {
                    // Remove this as dropable
                    m_drag_and_drop->remove_dropable(this);
                    object->set_max_column(2);

                    auto defensive_building = dynamic_cast<objects::defensive_building*>(m_object);
                    if (defensive_building) {
                        auto ai = std::make_shared<domain::map::ai::ai>();
                        ai->set_new_target_func([](domain::map::field* origin, domain::map::ai::ai* ai1) -> domain::combat::defender* {
                            if (!origin || !ai1->get_map() || !ai1->get_map()->get_game_level() || !ai1->get_current_field()) {
                                SDL_Log("Precondition(s) not met\n");
                                return nullptr;
                            }

//                            SDL_Log("Looking for tiles nearby %f:%f\n", origin->m_pos.x, origin->m_pos.y);

                            auto fields = ai1->get_map()->get_fields_in_range(2, origin); // Replace 2 with "ai1->get_unit()->get_range()"
                            if (fields.empty()) {
                                SDL_Log("No fields nearby\n");
                                return nullptr;
                            }

//                            SDL_Log("Found %i tile(s)\n", fields.size());

                            auto enemies = ai1->get_map()->get_game_level()->get_enemies_in_lvl();
                            if (enemies.empty()) {
                                SDL_Log("No enemies available\n");
                                return nullptr;
                            }

                            for (auto &field : fields) {
                                field.field->set_flags(domain::map::field::FLAG_NONE);
                            }

                            for (auto &enemy : enemies) {
                                for (auto &field : fields) {
                                    field.field->set_flags(domain::map::field::FLAG_TARGET | domain::map::field::FLAG_WEIGHT);

                                    if (field.field == enemy->get_current_field()) {
                                        return enemy.get();
                                    }
                                }
                            }

                            return nullptr;
                        });

                        ai->set_state(std::make_shared<ai::states::search_and_destroy_state>());
//            ai->set_unit(std::dynamic_pointer_cast<domain::combat::attacker>(defensive_building->shared_from_this()));
                        ai->set_map(std::shared_ptr<domain::map::map>(&m_map));
                        ai->set_current_field(shared_from_this());

//                        defensive_building->set_ai(ai);
                    }
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
        bool field::place_object(objects::field_object* object) {
            if (!has_object() && object != nullptr) {
                m_object = object;
                m_object->set_field(shared_from_this());

                // notify local observers
                notify_observers(this, "object-placed");

                return true;
            } else if (has_object() && object == nullptr) {
                // Remove the current placed object
                // First call the notifiers (so they can still access the object)
                notify_observers(this, "object-destroyed");
                // Reset the field
                m_object->set_field(nullptr);
                m_object = nullptr;

                // The field is now dropable
                m_drag_and_drop->add_dropable(*this);
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

        long field::get_weight() const {
            return m_weight;
        }

        void field::set_weight(long weight) {
            m_weight = weight;
        }

        unsigned int field::get_flags() const {
            return m_flags;
        }

        void field::set_flags(unsigned int flags) {
            m_flags = flags;
        }
    }
}

#endif //CITY_DEFENCE_BASE_FIELD_CPP
