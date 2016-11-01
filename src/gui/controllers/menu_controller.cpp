//
// Created by robbie on 29-10-2016.
//

#include "menu_controller.h"
#include "../../engine/eventbus/eventbus.h"
#include "../router.h"

namespace gui {
    namespace controllers {
        void menu_controller::show(int call, gui::views::main_menu &view) {
            if (call > 0) {
                // Last call, unsubscribe
                view.after_last_draw();
            } else {
                if (call < 0) {
                    // First call, subscribe on eventbus
                    view.before_first_draw();
                }

                // Draw the view
                view.draw();
            }
        }

        void menu_controller::quit(int call, engine::engine *engine1) {
            engine1->stop();
        }

        void menu_controller::play(int call){
            if (call < 0) {
                router::get_instance().go_back();
                SDL_Log("PLAY CLICKED Controller");
                router::get_instance().use_and_perform("main_map");
            }
        }
    }
}
