//
// Created by robbie on 14-11-2016.
//

#ifndef CITY_DEFENCE_CREDITS_H
#define CITY_DEFENCE_CREDITS_H

#include "base_view.h"
#include "../../engine/graphics/texture_manager.h"
#include "../../engine/graphics/font_manager.h"
#include "../../engine/graphics/color_manager.h"
#include "../../engine/window.h"
#include "../../engine/graphics/moveable_box.h"
#include "../../engine/engine.h"

namespace gui {
    namespace views {
        class credits : public base_view {
        public:
            credits(engine::graphics::texture_manager &texture_manager, engine::graphics::font_manager &font_manager,
                    engine::graphics::color_manager &color_manager, engine::window &window,
                    engine::audio::music_manager &music_manager);

            void before();

            void on_display_change(engine::math::box2_t display_box);

            void after();

            void draw(unsigned int time_elapsed, engine::math::box2_t display_box);

        private:
            engine::graphics::texture_manager &m_texture_manager;
            engine::graphics::font_manager &m_font_manager;
            engine::graphics::color_manager &m_color_manager;
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
