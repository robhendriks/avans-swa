//
// Created by Bert on 21-12-2016.
//

#ifndef CITY_DEFENCE_MAYOR_H
#define CITY_DEFENCE_MAYOR_H

#include <memory>
#include "base_view.h"
#include "../../domain/drawable/draw_managers_wrapper.h"

namespace gui {
    namespace views {
        class mayor_view : public base_view {
        public:
            mayor_view(domain::drawable::draw_managers_wrapper &draw_managers);

            void before();

            void on_display_change(engine::math::box2_t display_box);

            void draw(unsigned int time_elapsed, engine::math::box2_t display_box);

            void after();

        private:
            void change_show();

            bool m_show;

            std::unique_ptr<engine::math::box2_t> m_mayor_box;
            std::unique_ptr<engine::math::box2_t> m_mayor_text_box;

            domain::drawable::draw_managers_wrapper &m_draw_managers;
        };
    }
}


#endif //CITY_DEFENCE_MAYOR_H
