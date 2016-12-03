//
// Created by robbie on 2-12-2016.
//

#include "level_goals.h"
#include "../../engine/graphics/box_builder.h"

namespace gui {
    namespace views {

        level_goals::level_goals(models::level_goals_model &model, engine::graphics::texture_manager &texture_manager,
                                 engine::graphics::font_manager &font_manager) : m_model(model),
                                                                                 m_texture_manager(texture_manager),
                                                                                 m_font_manager(font_manager),
                                                                                 m_stats_header_box(nullptr) {

        }

        void level_goals::before() {
            // Load textures
            m_texture_manager.load_from_svg("images/ui-pack.svg", {{1255, 244}, {1454, 290}}, 1.5, "g_header");
            m_texture_manager.load_from_svg("images/ui-pack.svg", {{1255, 4}, {1454, 49}}, 1.5, "g_box");
            m_texture_manager.load_from_svg("images/ui-pack.svg", {{1255, 124}, {1454, 169}}, 1.5, "g_green_box");
            m_texture_manager.load_from_svg("images/ui-pack.svg", {{98, 544}, {136, 580}}, 1, "g_check");
            m_texture_manager.load_from_svg("images/ui-pack.svg", {{149, 694}, {187, 730}}, 1, "g_cross");

            // Load texts
            m_texture_manager.load_text("Goals", {255, 255, 255}, *m_font_manager.get_font("roboto", 25), "g_header_text");
        }

        void level_goals::on_display_change(engine::math::box2_t display_box) {
            engine::graphics::box_builder builder(m_texture_manager.get_size("g_header"));
            m_stats_header_box.reset(new engine::math::box2_t(builder.build()));
        }

        void level_goals::draw(unsigned int time_elapsed, engine::math::box2_t display_box) {
            m_texture_manager.draw("g_header", *m_stats_header_box);

            engine::graphics::box_builder builder1(m_texture_manager.get_size("g_header_text"));
            builder1.to_center(*m_stats_header_box);
            m_texture_manager.draw("g_header_text", builder1.build());

            engine::graphics::box_builder builder2(m_texture_manager.get_size("g_box"));
            builder2.as_left_top(m_stats_header_box->left_bottom());

            engine::graphics::box_builder builder3(m_texture_manager.get_size("g_check"));

            for (auto &goals : m_model.game_goals->get()) {
                // Draw stat box
                builder2.add_margin({0, 10});
                auto stat_box = builder2.build();

                // Center stat image
                builder3.as_left_top(stat_box.left_top()).center_vertical(stat_box.min.y, stat_box.max.y)
                    .add_margin({20, 0});

                auto image_box = builder3.build();

                // Draw stat image and text
                int goal_stat = m_model.game_stats->get_count(goals.first);
                std::string text = goals.first + ": " + std::to_string(goal_stat) + "/" + std::to_string(goals.second);
                text[0] = toupper(text[0]);
                if (goal_stat >= goals.second) {
                    // Goal is reached
                    m_texture_manager.draw("g_green_box", stat_box);
                    m_texture_manager.draw("g_check", image_box);
                } else {
                    // Goal not reached
                    m_texture_manager.draw("g_box", stat_box);
                    m_texture_manager.draw("g_cross", image_box);
                }

                m_texture_manager.load_text(text, {255, 0, 0}, *m_font_manager.get_font("roboto", 18), "g_text");

                // Draw the text
                engine::graphics::box_builder builder4(m_texture_manager.get_size("g_text"));
                builder4.as_left_top(image_box.right_top()).center_vertical(image_box.min.y, image_box.max.y)
                    .add_margin({10, 0});

                m_texture_manager.draw("g_text", builder4.build());
                m_texture_manager.unload("g_text");

                builder2.add_margin({0, stat_box.height()});
            }
        }

        void level_goals::after() {
            // Unload textures
            m_texture_manager.unload("g_header");
            m_texture_manager.unload("g_box");
            m_texture_manager.unload("g_green_box");
            m_texture_manager.unload("g_check");
            m_texture_manager.unload("g_cross");

            // Unload texts
            m_texture_manager.unload("g_header_text");
        }
    }
}
