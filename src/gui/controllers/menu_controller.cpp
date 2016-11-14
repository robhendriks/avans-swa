//
// Created by robbie on 29-10-2016.
//

#include "menu_controller.h"

namespace gui {
    namespace controllers {

        menu_controller::menu_controller(views::main_menu &main_menu, engine::engine &engine,
                                         controllers::main_map_controller &main_map_controller, game &game1
                , services::level_loader::base_map_loader &map_loader)
            : base_controller(game1), m_engine(engine), m_main_menu(main_menu),
              m_main_map_controller(main_map_controller), _map_loader(map_loader) {

            m_main_menu.set_controller(*this);
        }

        void menu_controller::show() {
            view(m_main_menu);
            m_main_menu.set_controller(*this);
        }

        void menu_controller::play() {
            m_main_map_controller.show();
        }

        void menu_controller::load() {
//            TODO: load map (level1)
            _game_world = this->_map_loader.load("level1.json");
            m_main_map_controller.show();
        }

        void menu_controller::quit() {
            m_engine.stop();
        }
    }
}
