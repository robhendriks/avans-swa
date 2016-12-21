//
// Created by Mark on 5-12-2016.
//

#include "defensive_building.h"
#include "../../../engine/graphics/box_builder.h"

#ifndef CITY_DEFENCE_BUILDING_CPP
#define CITY_DEFENCE_BUILDING_CPP

namespace domain {
    namespace map {
        namespace objects {

            defensive_building::defensive_building(engine::math::box2_t box, const std::string &id, int hitpoints,
                                                   double health_ragen, const std::string &name,
                                                   const std::vector<std::shared_ptr<resources::resource>> &required_resources,
                                                   int _range, int _min_dmg, int _max_dmg) : building(box,id,hitpoints,health_ragen,name,required_resources) {
                range = _range;
                min_dmg = _min_dmg;
                max_dmg = _max_dmg;
            }

            defensive_building::defensive_building(std::shared_ptr<field> field1, int _range, int _min_dmg,
                                                   int _max_dmg) : building(field1) {
                range = _range;
                min_dmg = _min_dmg;
                max_dmg = _max_dmg;
            }

            defensive_building::defensive_building(const defensive_building &obj)
                : domain::drawable::drawable_game_object(obj), building(obj) {
                range = obj.range;
                min_dmg = obj.min_dmg;
                max_dmg = obj.max_dmg;
            }

            int defensive_building::get_min_dmg() {
                return min_dmg;
            }

            int defensive_building::get_max_dmg() {
                return max_dmg;
            }

            int defensive_building::get_range() {
                return range;
            }

            void defensive_building::update(domain::game_level::game_level game_level) {
                //TODO
            }

            dragable_field_object *defensive_building::clone() const {
                return new defensive_building(*this);
            }

            void defensive_building::draw(drawable::draw_managers_wrapper &draw_managers, unsigned int time_elapsed) {
                building::draw(draw_managers, time_elapsed);

                if ((show_hover_info || m_field == nullptr) && !m_drag_and_drop->is_dragging(this)) {
                    // Show damage
                    auto &font = *draw_managers.font_manager.get_font("roboto", 12);

                    draw_managers.texture_manager.load_text("Damage:", {0, 0, 0}, font, "d_d_title");
                    engine::graphics::box_builder builder(draw_managers.texture_manager.get_size("d_d_title"));
                    builder.as_right_bottom(get_box().left_top()).add_margin({0, 0});
                    auto title_box = builder.build();
                    draw_managers.texture_manager.draw("d_d_title", title_box);
                    draw_managers.texture_manager.unload("d_d_title");

                    // Load the text
                    std::string text = std::to_string(get_min_dmg()) + " - " + std::to_string(get_max_dmg());
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
