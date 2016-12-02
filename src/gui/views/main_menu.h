//
// Created by te on 25-Oct-16.
//

#ifndef CITY_DEFENCE_MENU_GUI_H
#define CITY_DEFENCE_MENU_GUI_H

#include "../../engine/audio/music_manager.h"
#include "base_view.h"
#include "top_bar.h"

namespace gui {
    namespace controllers {
        class menu_controller;
    }
}

namespace gui {
    namespace views {
        class top_bar;
    }
}

namespace gui {
    namespace views {
        class main_menu : public base_view,
                          engine::eventbus::subscriber<engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT>> {
        public:
            main_menu(top_bar &top_bar1, engine::audio::music_manager &music_manager);

            void before();

            void layout(engine::math::box2_t display_box);

            void draw(unsigned int time_elapsed, engine::math::box2_t display_box);

            void after();

            void on_event(engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT> &event);

            void set_controller(std::shared_ptr<controllers::menu_controller> menu_controller);

        private:
            top_bar &m_top_bar;
            engine::audio::music_manager &m_music_manager;
            engine::math::box2_t m_play_dest;
            engine::math::box2_t m_load_dest;
            engine::math::box2_t m_quit_dest;
        };
    }
}

#endif //CITY_DEFENCE_MENU_GUI_H
