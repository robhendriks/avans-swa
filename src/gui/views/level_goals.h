//
// Created by robbie on 2-12-2016.
//

#ifndef CITY_DEFENCE_LEVEL_GOALS_H
#define CITY_DEFENCE_LEVEL_GOALS_H

#include "base_view.h"
#include "../../engine/graphics/texture_manager.h"
#include "../../engine/graphics/font_manager.h"
#include "../models/level_goals_model.h"

namespace gui {
    namespace views {
        class level_goals : public base_view {
            friend class level;
        public:
            level_goals(models::level_goals_model &model, engine::graphics::texture_manager &texture_manager,
                        engine::graphics::font_manager &font_manager);

            void before();

            void on_display_change(engine::math::box2_t display_box);

            void draw(unsigned int time_elapsed, engine::math::box2_t display_box);

            void after();

        private:
            models::level_goals_model &m_model;
            engine::graphics::texture_manager &m_texture_manager;
            engine::graphics::font_manager &m_font_manager;
            std::unique_ptr<engine::math::box2_t> m_stats_header_box;
        };
    }
}


#endif //CITY_DEFENCE_LEVEL_GOALS_H
