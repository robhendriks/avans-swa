//
// Created by robbie on 29-10-2016.
//

#include "menu_controller.h"

namespace gui {
    namespace controllers {

        void menu_controller::show(gui::views::main_menu &view) {
            view.draw();
        }

        void menu_controller::quit(engine::engine *engine1) {
            engine1->stop();
        }
    }
}
