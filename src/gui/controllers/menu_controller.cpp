//
// Created by robbie on 29-10-2016.
//

#include "menu_controller.h"
#include "../../engine/eventbus/eventbus.h"

namespace gui {
    namespace controllers {

        void menu_controller::show(int call, gui::views::main_menu &view) {
            if (call > 0) {
                // Last call, unsubscribe
                engine::eventbus::eventbus<engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT>>::get_instance().unsubscribe(&view);

                view.after_last_draw();
            } else {
                if (call < 0) {
                    // First call, subscribe on eventbus
                    engine::eventbus::eventbus<engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT>>::get_instance().subscribe(&view);

                    view.before_first_draw();
                }

                // Draw the view
                view.draw();
            }
        }

        void menu_controller::quit(int call, engine::engine *engine1) {
            engine1->stop();
        }
    }
}
