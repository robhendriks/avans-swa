//
// Created by te on 25-Oct-16.
//

#ifndef CITY_DEFENCE_MENU_GUI_H
#define CITY_DEFENCE_MENU_GUI_H

#include "../../engine/eventbus/subscriber.h"
#include "../../engine/events/mouse_button_down.h"
#include "../../engine/graphics/texture_manager.h"
#include "../../engine/input/mouse_buttons.h"

namespace gui {
    namespace views {
        class main_menu : public engine::eventbus::subscriber<engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT>> {
        public:
            main_menu(engine::graphics::texture_manager &texture_manager);

            void before_first_draw();

            void draw();

            void after_last_draw();

            void on_event(engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT> &event);
        private:
            engine::graphics::texture_manager& m_texture_manager;
            engine::math::box2_t m_play_dest;
            engine::math::box2_t m_load_dest;
            engine::math::box2_t m_quit_dest;
        };
    }
}

#endif //CITY_DEFENCE_MENU_GUI_H
