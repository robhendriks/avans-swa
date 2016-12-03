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
                                                                                 m_stats_box(nullptr) {

        }

        void level_goals::before() {
            // Load textures
            m_texture_manager.load_from_svg("images/ui-pack.svg", {{1, 310}, {101, 410}}, m_model.game_goals->get().size() * 3, "g_box");
            m_texture_manager.load_from_svg("images/ui-pack.svg", {{103, 600}, {130, 625}}, 1, "g_check");
            m_texture_manager.load_from_svg("images/ui-pack.svg", {{155, 650}, {182, 675}}, 1, "g_cross");
        }

        void level_goals::on_display_change(engine::math::box2_t display_box) {
            engine::graphics::box_builder builder(m_texture_manager.get_size("g_box"));
            m_stats_box.reset(new engine::math::box2_t(builder.build()));
        }

        void level_goals::draw(unsigned int time_elapsed, engine::math::box2_t display_box) {
            m_texture_manager.draw("g_box", *m_stats_box);

            engine::graphics::box_builder builder1(m_texture_manager.get_size("g_check"));
            builder1.as_left_top(m_stats_box->left_top()).add_margin({20, 20});

            for (auto &goals : m_model.game_goals->get()) {
                auto image_box = builder1.build();
                if (m_model.game_stats->get_count(goals.first) >= goals.second) {
                    // Goal is reached
                    m_texture_manager.draw("g_check", image_box);
                    m_texture_manager.load_text(goals.first, {0, 127, 14}, *m_font_manager.get_font("roboto", 18), "g_text");
                } else {
                    // Goal not reached
                    m_texture_manager.draw("g_cross", image_box);
                    m_texture_manager.load_text(goals.first, {255, 50, 50}, *m_font_manager.get_font("roboto", 18), "g_text");
                }

                // Draw the text
                engine::graphics::box_builder builder2(m_texture_manager.get_size("g_text"));
                builder2.as_left_top(image_box.right_top()).center_vertical(image_box.min.y, image_box.max.y)
                    .add_margin({10, 0});

                m_texture_manager.draw("g_text", builder2.build());
                m_texture_manager.unload("g_text");

                builder1.add_margin({0, 50});
            }
        }

        void level_goals::after() {
            // Unload textures
            m_texture_manager.unload("g_box");
            m_texture_manager.unload("g_check");
            m_texture_manager.unload("g_cross");
        }
    }
}
