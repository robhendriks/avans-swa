//
// Created by te on 01-Nov-16.
//

#ifndef CITY_DEFENCE_MAIN_MAP_CONTROLLER_H
#define CITY_DEFENCE_MAIN_MAP_CONTROLLER_H

#include "../views/main_map.h"
#include "../../domain/map/map.h"

namespace gui {
    namespace controllers {
        class main_map_controller {
        public:
            main_map_controller(engine::window &window);
            ~main_map_controller();
            void show(int call, gui::views::main_map &view);
            void click_tile(int call);
        private:
            engine::window &m_window;
            models::main_map_model *m_main_map_model;
            domain::map::map *m_map;
        };
    }
}

#endif //CITY_DEFENCE_MAIN_MAP_CONTROLLER_H
