//
// Created by robbie on 14-11-2016.
//

#ifndef CITY_DEFENCE_CREDITS_H
#define CITY_DEFENCE_CREDITS_H

#include "base_view.h"
#include "../../engine/graphics/moveable_box.h"
#include "../../domain/drawable/draw_managers_wrapper.h"
#include "../../engine/audio/music_manager.h"
#include "top_bar.h"

namespace gui {
    namespace views {
        class top_bar;
    }
}

namespace gui {
    namespace views {
        class credits : public base_view,
                        engine::eventbus::subscriber<engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT>>,
                        engine::eventbus::subscriber<engine::events::key_down> {
        public:
            credits(top_bar &top_bar1, engine::audio::music_manager &music_manager);

            void before();

            void on_display_change(engine::math::box2_t display_box);

            void after();

            void draw(unsigned int time_elapsed, engine::math::box2_t display_box);

            void on_event(engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT> &event);

            void on_event(engine::events::key_down &event);

        private:
            top_bar &m_top_bar;
            engine::audio::music_manager &m_music_manager;
            std::unique_ptr<engine::math::box2_t> m_header_box;
            std::unique_ptr<engine::math::box2_t> m_credits_box;
            std::unique_ptr<engine::math::box2_t> m_title_box;
            std::unique_ptr<engine::graphics::moveable_box> m_moveable_box;
            std::unique_ptr<engine::math::box2_t> m_back_box;
            std::unique_ptr<engine::math::box2_t> m_back_text_box;
            std::unique_ptr<engine::math::box2_t> m_back_slider_box;
            std::unique_ptr<engine::graphics::moveable_box> m_moveable_slider_box;
            std::unique_ptr<engine::graphics::moveable_box> m_moveable_special_box;
            std::vector<std::string> m_names;
            std::vector<std::string> m_special_thanks;
            bool m_at_slow_speed;
        };
    }
}

#endif //CITY_DEFENCE_CREDITS_H
