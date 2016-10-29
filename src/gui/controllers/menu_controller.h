//
// Created by robbie on 29-10-2016.
//

#ifndef CITY_DEFENCE_MENU_CONTROLLER_H
#define CITY_DEFENCE_MENU_CONTROLLER_H

#include "../../engine/engine.h"
#include "../views/main_menu.h"

namespace gui {
    namespace controllers {
        class menu_controller {
        public:
            void show(gui::views::main_menu &view);
            void quit(engine::engine *engine1);
        };
    }
}

#endif //CITY_DEFENCE_MENU_CONTROLLER_H
