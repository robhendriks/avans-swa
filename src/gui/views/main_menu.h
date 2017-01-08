//
// Created by te on 25-Oct-16.
//

#ifndef CITY_DEFENCE_MENU_GUI_H
#define CITY_DEFENCE_MENU_GUI_H

#include "../../engine/audio/music_manager.h"
#include "../../engine/events/mouse_motion.h"
#include "../../engine/events/key_down.h"
#include "base_view.h"
#include "help.h"

namespace gui {
    namespace controllers {
        class menu_controller;
    }
}

namespace gui {
    namespace views {
        class help;
    }
}

namespace gui {
    namespace views {
        class main_menu : public base_view,
                          engine::eventbus::subscriber<engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT>>,
                          engine::eventbus::subscriber<engine::events::mouse_motion>,
                          engine::eventbus::subscriber<engine::events::key_down> {
        public:
            main_menu(help &help_view, engine::audio::music_manager &music_manager, engine::audio::sound_manager &sound_manager);

            void before();

            void on_display_change(engine::math::box2_t display_box);

            void draw(unsigned int time_elapsed, engine::math::box2_t display_box);

            void after();

            void on_event(engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT> &event);

            void on_event(engine::events::mouse_motion &event);

            void on_event(engine::events::key_down &event);

            void set_controller(controllers::menu_controller &menu_controller);

        private:
            void set_sliders(unsigned int pos, bool force = false);

            void menu_btn_click(engine::math::vec2_t mouse_pos);

            help &m_help_view;
            engine::audio::music_manager &m_music_manager;
            engine::audio::sound_manager &m_sound_manager;
            std::unique_ptr<engine::math::box2_t> m_logo_box;
            std::unique_ptr<engine::math::box2_t> m_play_btn_box;
            std::unique_ptr<engine::math::box2_t> m_play_text_box;
            std::unique_ptr<engine::math::box2_t> m_help_btn_box;
            std::unique_ptr<engine::math::box2_t> m_help_text_box;
            std::unique_ptr<engine::math::box2_t> m_load_btn_box;
            std::unique_ptr<engine::math::box2_t> m_load_text_box;
            std::unique_ptr<engine::math::box2_t> m_credits_btn_box;
            std::unique_ptr<engine::math::box2_t> m_credits_text_box;
            std::unique_ptr<engine::math::box2_t> m_slider_left_box;
            std::unique_ptr<engine::math::box2_t> m_slider_right_box;
            std::vector<engine::math::box2_t> m_slider_positions;
            unsigned int m_current_slider_pos;
        };
    }
}

#endif //CITY_DEFENCE_MENU_GUI_H
