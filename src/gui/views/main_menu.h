//
// Created by te on 25-Oct-16.
//

#ifndef CITY_DEFENCE_MENU_GUI_H
#define CITY_DEFENCE_MENU_GUI_H

#include "../../engine/eventbus/subscriber.h"
#include "../../engine/events/mouse_button_down.h"
#include "../../engine/graphics/texture_manager.h"
#include "../../engine/input/mouse_buttons.h"
#include "base_view.h"
#include "../controllers/menu_controller.h"

namespace gui {
    namespace controllers {
        class menu_controller;
    }
}

namespace gui {
    namespace views {
        class main_menu
            : public base_view,
              engine::eventbus::subscriber<engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT>> {
        public:
            main_menu(engine::graphics::texture_manager &texture_manager, engine::audio::music_manager &music_manager);

            void set_controller(controllers::menu_controller &menu_controller);

            void before();

            void draw(unsigned int time_elapsed, engine::math::box2_t display_box);

            void after();

            void on_event(engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT> &event);

        private:
            engine::graphics::texture_manager &m_texture_manager;
            engine::audio::music_manager &m_music_manager;
            controllers::menu_controller *m_menu_controller;
            engine::math::box2_t m_play_dest;
            engine::math::box2_t m_load_dest;
            engine::math::box2_t m_quit_dest;
        };
    }
}

#endif //CITY_DEFENCE_MENU_GUI_H
