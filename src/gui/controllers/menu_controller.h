//
// Created by robbie on 29-10-2016.
//

#ifndef CITY_DEFENCE_MENU_CONTROLLER_H
#define CITY_DEFENCE_MENU_CONTROLLER_H

#include "../../engine/engine.h"
#include "../views/main_menu.h"
#include "base_controller.h"
#include "main_map_controller.h"
#include "../../services/map_loader/base_map_loader.h"

namespace gui {
    namespace views {
        class main_menu;
    }
}

namespace gui {
    namespace controllers {
        class menu_controller : public base_controller {
        public:
            menu_controller(views::main_menu &main_menu, engine::engine &engine,
                            controllers::main_map_controller &main_map_controller, game &game1, services::map_loader::base_map_loader &map_loader);

            void show();

            void play();

            void load();

            void quit();

        private:
            engine::engine &m_engine;
            views::main_menu &m_main_menu;
            controllers::main_map_controller &m_main_map_controller;
            services::map_loader::base_map_loader &_map_loader;
            domain::gameworld::game_world _game_world;
        };
    }
}

#endif //CITY_DEFENCE_MENU_CONTROLLER_H
