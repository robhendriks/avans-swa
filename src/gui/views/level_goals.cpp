//
// Created by robbie on 2-12-2016.
//

#include "level_goals.h"

namespace gui {
    namespace views {

        level_goals::level_goals(models::level_goals_model &model, engine::graphics::texture_manager &texture_manager,
                                 engine::graphics::font_manager &font_manager) : m_model(model),
                                                                                 m_texture_manager(texture_manager),
                                                                                 m_font_manager(font_manager) {

        }

        void level_goals::before() {
            m_texture_manager.load("images/green_check", "g_check");
            m_texture_manager.load("images/green_cross", "g_cross");
        }

        void level_goals::on_display_change(engine::math::box2_t display_box) {

        }

        void level_goals::draw(unsigned int time_elapsed, engine::math::box2_t display_box) {
//            for (auto info : m_model.game_goals->get_info()) {
//                m_model.game_stats->get_count();
//            }
        }

        void level_goals::after() {
            m_texture_manager.unload("g_check");
            m_texture_manager.unload("g_cross");
        }
    }
}
