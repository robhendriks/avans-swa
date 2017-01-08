#ifndef CITY_DEFENCE_BUILDING_CPP
#define CITY_DEFENCE_BUILDING_CPP

#include "building.h"
#include "road.h"
#include "../../../engine/graphics/box_builder.h"

namespace domain {
    namespace map {
        namespace objects {

            building::building(field &field1, const std::string &id, int hitpoints, double health_ragen,
                               const std::string &name,
                               const std::vector<resources::resource*> &required_resources) :
                dragable_field_object(field1), domain::combat::defender(hitpoints, 0), id(id), health_ragen(health_ragen), name(name),
                required_resources(required_resources), show_hover_info(false)
            {
                // Subscribe to event
                engine::eventbus::eventbus::get_instance().subscribe(this);
            }

            building::building(const engine::math::box2_t &box, const std::string &id, int hitpoints,
                               double health_ragen, const std::string &name,
                               const std::vector<resources::resource*> &required_resources
            )
                : dragable_field_object(box), domain::combat::defender(hitpoints, 0), id(id), health_ragen(health_ragen), name(name),
                  required_resources(required_resources), show_hover_info(false) {
                // Subscribe to event
                engine::eventbus::eventbus::get_instance().subscribe(this);
            }

            building::~building() {
                // Unsubscribe to event
                engine::eventbus::eventbus::get_instance().unsubscribe(this);
            }

            // Copy constructor
            building::building(const building &obj) : dragable_field_object(obj), domain::combat::defender(obj) {
                id = obj.id;
                health_ragen = obj.health_ragen;
                name = obj.name;
                required_resources = obj.required_resources;
                show_hover_info = false;

                // Subscribe to event
                engine::eventbus::eventbus::get_instance().subscribe(this);
            }

            /**
             * Make sure a building can only be placed next to a road object
             *
             * @param field1
             * @return
             */
            bool building::can_place_on(field &field1) const {
                for (auto &neighbor : field1.get_neighbors()) {
                    if (neighbor->has_object() && dynamic_cast<road*>(neighbor->get_object())) {
                        return true;
                    }
                }

                return false;
            }

            dragable_field_object *building::clone() const {
                return new building(*this);
            }

            std::vector<domain::resources::resource*> building::get_required_resources() {
                return required_resources;
            }

            void building::update(domain::game_level::game_level &game_level) {

            }

            void building::update_game_stats(domain::game_level::game_stats &game_stats1, std::string action) {
                if (action == "object-placed") {
                    game_stats1.increase("buildings");
                } else if (action == "object-destroyed") {
                    game_stats1.decrease("buildings");
                }
            }

            int building::lower_hitpoints(int by) {
                int result = domain::combat::defender::lower_hitpoints(by);
                if (result == 0) {
                    m_field->place_object(nullptr);
                }
                return result;
            }

            void building::set_draw_settings(std::string file_loc, engine::math::vec2_t image_start_position) {
                dragable_field_object::set_draw_settings(file_loc, image_start_position);
            }

            void building::set_box(engine::math::box2_t box) {
                dragable_field_object::set_box(box);
            }

            engine::math::box2_t building::get_box() const {
                return dragable_field_object::get_box();
            }

            void building::on_event(engine::events::mouse_motion &event) {
                if (id != "" && !m_drag_and_drop->is_dragging()) {
                    if (get_box().contains(event.get_mouse_position())) {
                        show_hover_info = true;
                        return;
                    }
                }

                show_hover_info = false;
            }

            void building::draw(drawable::draw_managers_wrapper &draw_managers, unsigned int time_elapsed) {
                // Draw the object
                dragable_field_object::draw(draw_managers, time_elapsed);

                // Show resource costs when the building is not placed
                if (m_field == nullptr && !m_drag_and_drop->is_dragging(this)) {
                    auto &font = *draw_managers.font_manager.get_font("roboto", 12);

                    // Show resource costs
                    draw_managers.texture_manager.load_text("Costs:", {0, 0, 0}, font, "b_c_title");
                    engine::graphics::box_builder builder(draw_managers.texture_manager.get_size("b_c_title"));
                    builder.as_left_bottom(get_box().right_top()).add_margin({5, 0});
                    auto title_box = builder.build();
                    draw_managers.texture_manager.draw("b_c_title", title_box);
                    draw_managers.texture_manager.unload("b_c_title");

                    // Show resource info
                    float y_margin = 2;
                    for (auto resource : required_resources) {
                        // Load the text
                        std::string text = resource->get_resource_type() + ": " + std::to_string(resource->get_count());
                        draw_managers.texture_manager.load_text(text, {0, 0, 0}, font, "hover");
                        // Draw
                        engine::graphics::box_builder builder1(draw_managers.texture_manager.get_size("hover"));
                        builder1.as_left_top(title_box.left_bottom()).add_margin({0, y_margin});
                        draw_managers.texture_manager.draw("hover", builder1.build());

                        // Increase y margin
                        y_margin += builder.build().height() + 2;

                        // Unload the text
                        draw_managers.texture_manager.unload("hover");
                    }
                }
            }
        }
    }
}

#endif //CITY_DEFENCE_BUILDING_CPP
