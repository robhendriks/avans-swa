//
// Created by Bert on 21-12-2016.
//

#ifndef CITY_DEFENCE_MAYOR_VIEW_H
#define CITY_DEFENCE_MAYOR_VIEW_H

#include <memory>
#include "base_view.h"
#include "../../domain/drawable/draw_managers_wrapper.h"
#include "../../domain/mayor/mayor.h"

namespace gui {
    namespace views {
        enum view_state { visible, hidden, animating};

        class mayor_view : public base_view {
        public:
            mayor_view(domain::drawable::draw_managers_wrapper &draw_managers);

            void before();

            void on_display_change(engine::math::box2_t display_box);

            void draw(unsigned int time_elapsed, engine::math::box2_t display_box);

            void after();

            void set_mayor(std::shared_ptr<domain::mayor> _mayor);

            void set_current_response(const std::string &response);

        private:
            void change_show();

            void set_boxes(const engine::math::box2_t display_box);

            bool m_show;
            std::shared_ptr<domain::mayor> m_mayor;

            std::unique_ptr<engine::math::box2_t> m_mayor_box;
            std::unique_ptr<engine::math::box2_t> m_mayor_text_box;
            std::shared_ptr<engine::math::box2_t> m_init_box;
            std::unique_ptr<engine::math::box2_t> m_dest_box;

            domain::drawable::draw_managers_wrapper &m_draw_managers;
            unsigned int m_last_transition_time = 0;
            unsigned int m_current_display_time = 0;
            std::string m_current_response = "I have nothing to say...";
            unsigned int m_max_display_time = 5000;
            unsigned int m_max_animation_time = 1000;
            unsigned int m_time_moved = 0;
            view_state m_state = animating;
            view_state m_previous_state = hidden;

        };
    }
}


#endif //CITY_DEFENCE_MAYOR_VIEW_H
