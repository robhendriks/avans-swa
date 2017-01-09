//
// Created by Mark on 5-12-2016.
//

#include <string>
#include "defensive_building.h"
#include "../../../engine/graphics/box_builder.h"

#ifndef CITY_DEFENCE_BUILDING_CPP
#define CITY_DEFENCE_BUILDING_CPP

namespace domain {
    namespace map {
        namespace objects {

            defensive_building::defensive_building(const engine::math::box2_t &box,
                                                   const std::string &id,
                                                   int hitpoints,
                                                   double health_ragen,
                                                   const std::string &name,
                                                   const std::vector<resources::resource*> &required_resources,
                                                   int range,
                                                   int min_damage,
                                                   int max_damage)
                : building(box, id, hitpoints, health_ragen, name, required_resources),
                  attacker(min_damage, max_damage, 2.0, range, 0) {}

            void defensive_building::update(domain::game_level::game_level &game_level, unsigned int elapsed_time) {
                if(get_ai()){
                    get_ai()->update(elapsed_time);
                }
            }

            dragable_field_object* defensive_building::clone() const {
                return new defensive_building(*this);
            }

            void defensive_building::draw(drawable::draw_managers_wrapper &draw_managers, unsigned int time_elapsed) {
                building::draw(draw_managers, time_elapsed);

                if ((show_hover_info || m_field == nullptr) && !m_drag_and_drop->is_dragging(this)) {
                    // Show damage
                    auto &font = *draw_managers.font_manager.get_font("roboto", 12);

                    draw_managers.texture_manager.load_text("Damage:", {0, 0, 0}, font, "d_d_title");
                    engine::graphics::box_builder builder(draw_managers.texture_manager.get_size("d_d_title"));
                    builder.as_right_bottom(get_box().left_top());
                    auto title_box = builder.build();
                    draw_managers.texture_manager.draw("d_d_title", title_box);
                    draw_managers.texture_manager.unload("d_d_title");

                    // Load the text
                    std::string text = std::to_string(get_min_damage()) + " - " + std::to_string(get_max_damage());
                    draw_managers.texture_manager.load_text(text, {0, 0, 0}, font, "hover");
                    // Draw
                    engine::graphics::box_builder builder1(draw_managers.texture_manager.get_size("hover"));
                    builder1.as_left_top(title_box.left_bottom()).add_margin({0, 0});
                    draw_managers.texture_manager.draw("hover", builder1.build());

                    // Unload the text
                    draw_managers.texture_manager.unload("hover");

                    if (m_field != nullptr) {
                        auto hp = get_current_hp_percentage_relative_to_max();

                        // The whole box
                        engine::graphics::box_builder box_builder({32, 12});
                        box_builder.as_left_top(builder1.build().left_bottom()).add_margin({0, 2});
                        auto whole_box = box_builder.build();
                        draw_managers.color_manager.draw({255, 255, 255}, whole_box);

                        // The green box
                        engine::graphics::box_builder green_builder({static_cast<float>(hp * 30 / 100), 10});
                        green_builder.as_left_top(whole_box.left_top()).add_margin({1, 1});
                        auto green_box = green_builder.build();
                        draw_managers.color_manager.draw({0, 127, 14}, green_box);

                        // The red box
                        engine::graphics::box_builder red_builder({whole_box.width() - green_box.width() - 2, 10});
                        red_builder.as_left_top(green_box.right_top());
                        auto red_box = red_builder.build();
                        draw_managers.color_manager.draw({127, 0, 0}, red_box);
                    }
                }
            }
        }
    }
}

#endif //CITY_DEFENCE_BUILDING_CPP
