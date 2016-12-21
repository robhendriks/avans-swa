//
// Created by Mark on 5-12-2016.
//

#include "economic_building.h"
#include "../../../engine/graphics/box_builder.h"

#ifndef CITY_DEFENCE_BUILDING_CPP
#define CITY_DEFENCE_BUILDING_CPP

namespace domain {
    namespace map {
        namespace objects {

            economic_building::economic_building(engine::math::box2_t box, const std::string &id, int hitpoints,
                                                 double health_ragen, const std::string &name,
                                                 const std::vector<std::shared_ptr<resources::resource>> &required_resources,
                                                 std::shared_ptr<domain::resources::resource> resource) : building(
                box, id, hitpoints, health_ragen, name, required_resources ) {
                produced_resources = resource;
            }

            economic_building::economic_building(std::shared_ptr<field> field1,
                                                 std::shared_ptr<domain::resources::resource> resource) : building(
                field1) {
                produced_resources = resource;
            }

            economic_building::economic_building(const economic_building &obj) :
                domain::drawable::drawable_game_object(obj), building(obj) {
                produced_resources = obj.produced_resources;
            }

            dragable_field_object *economic_building::clone() const {
                return new economic_building(*this);
            }

            std::shared_ptr<domain::resources::resource> economic_building::get_produced_resources() {
                return produced_resources;
            }

            void economic_building::set_produced_resource(std::shared_ptr<domain::resources::resource> resource) {
                produced_resources = resource;
            }

            void economic_building::update(domain::game_level::game_level game_level) {
                int counter = 0;
                auto resourcelist = game_level.get_resources();
                for (auto resource:resourcelist) {
                    if (resource->get_resource_type() == produced_resources->get_resource_type()) {

                        //Update gamelevel
                        resourcelist[counter]->set_count(
                            resourcelist[counter]->get_count() + produced_resources->get_count());
                        game_level.set_resources(resourcelist);
                        break;
                    }
                    counter++;
                }
            }

            void economic_building::draw(drawable::draw_managers_wrapper &draw_managers, unsigned int time_elapsed) {
                building::draw(draw_managers, time_elapsed);

                if ((show_hover_info || m_field == nullptr) && !m_drag_and_drop->is_dragging(this)) {
                    // Show produced resources
                    auto &font = *draw_managers.font_manager.get_font("roboto", 12);

                    // Show resource produce
                    draw_managers.texture_manager.load_text("Produce per 1.5s:", {0, 0, 0}, font, "e_p_title");
                    engine::graphics::box_builder builder(draw_managers.texture_manager.get_size("e_p_title"));
                    builder.as_right_bottom(get_box().left_top()).add_margin({0, 0});
                    auto title_box = builder.build();
                    draw_managers.texture_manager.draw("e_p_title", title_box);
                    draw_managers.texture_manager.unload("e_p_title");

                    // Show produce info
                    // Load the text
                    std::string text = produced_resources->get_resource_type() + ": " + std::to_string(produced_resources->get_count());
                    draw_managers.texture_manager.load_text(text, {0, 0, 0}, font, "hover");
                    // Draw
                    engine::graphics::box_builder builder1(draw_managers.texture_manager.get_size("hover"));
                    builder1.as_left_top(title_box.left_bottom()).add_margin({0, 2});
                    draw_managers.texture_manager.draw("hover", builder1.build());

                    // Unload the text
                    draw_managers.texture_manager.unload("hover");

                    if (m_field != nullptr) {
                        engine::graphics::box_builder builder2({30, 10});
                        builder2.as_left_top(builder1.build().left_bottom()).add_margin({0, 2});

                        draw_managers.color_manager.draw({0, 0, 0}, builder2.build());
                        draw_managers.color_manager.draw({0, 127, 14}, builder2.build());
                    }
                }
            }
        }
    }
}

#endif //CITY_DEFENCE_BUILDING_CPP
