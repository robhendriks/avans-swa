//
// Created by te on 01-Nov-16.
//

#ifndef CITY_DEFENCE_MAIN_MAP_CONTROLLER_H
#define CITY_DEFENCE_MAIN_MAP_CONTROLLER_H

#include "../views/main_map.h"

namespace gui {
    namespace controllers {
        class main_map_controller {
        public:
            void show(int call, gui::views::main_map &view);
        };
    }
}

#endif //CITY_DEFENCE_MAIN_MAP_CONTROLLER_H
