//
// Created by robbie on 14-11-2016.
//

#ifndef CITY_DEFENCE_CREDITS_H
#define CITY_DEFENCE_CREDITS_H

#include "base_view.h"
#include "../../engine/window.h"
#include "../../engine/graphics/moveable_box.h"
#include "../../engine/engine.h"
#include "../../domain/drawable/draw_managers_wrapper.h"

namespace gui {
    namespace views {
        class credits : public base_view {
        public:
            credits(domain::drawable::draw_managers_wrapper &draw_managers, engine::window &window,
                    engine::audio::music_manager &music_manager);

            void before();

            void on_display_change(engine::math::box2_t display_box);

            void after();

            void draw(unsigned int time_elapsed, engine::math::box2_t display_box);

        private:
            domain::drawable::draw_managers_wrapper &m_draw_managers;
            engine::audio::music_manager &m_music_manager;
            engine::window &m_window;
            std::unique_ptr<engine::math::box2_t> m_header_box;
            std::unique_ptr<engine::math::box2_t> m_credits_box;
            std::unique_ptr<engine::math::box2_t> m_title_box;
            std::unique_ptr<engine::graphics::moveable_box> m_moveable_box;
            std::vector<std::string> m_names;
        };
    }
}

#endif //CITY_DEFENCE_CREDITS_H
