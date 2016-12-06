//
// Created by robbie on 2-12-2016.
//

#ifndef CITY_DEFENCE_LEVEL_GOALS_H
#define CITY_DEFENCE_LEVEL_GOALS_H

#include "base_view.h"
#include "../models/level_goals_model.h"
#include "../../domain/drawable/draw_managers_wrapper.h"

namespace gui {
    namespace views {
        class level_goals : public base_view {
            friend class level;
            friend class win_game_over;
        public:
            level_goals(models::level_goals_model &model, domain::drawable::draw_managers_wrapper &draw_managers);

            void before();

            void on_display_change(engine::math::box2_t display_box);

            void draw(unsigned int time_elapsed, engine::math::box2_t display_box);

            void after();

        private:
            models::level_goals_model &m_model;
            domain::drawable::draw_managers_wrapper &m_draw_managers;
            std::unique_ptr<engine::math::box2_t> m_stats_header_box;
        };
    }
}


#endif //CITY_DEFENCE_LEVEL_GOALS_H
