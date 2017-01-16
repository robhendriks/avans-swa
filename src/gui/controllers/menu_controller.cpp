//
// Created by robbie on 29-10-2016.
//

#include "menu_controller.h"

namespace gui {
    namespace controllers {

        menu_controller::menu_controller(views::main_menu &main_menu, engine::engine &engine,
                                         controllers::main_map_controller &main_map_controller,
                                         controllers::load_controller &load_controller,
                                         controllers::credits_controller &credits_controller, game &game1,
                                         services::world_loader::base_world_loader &world_loader)
            : base_controller(game1), m_engine(engine), m_main_menu(main_menu),
              m_main_map_controller(main_map_controller), m_load_controller(load_controller),
              m_credits_controller(credits_controller),
              m_world_loader(world_loader) {

            main_map_controller.set_menu_controller(*this);
            m_main_menu.set_controller(*this);
        }

        void menu_controller::show() {
            view(m_main_menu);
        }

        void menu_controller::play() {
            auto *world = m_world_loader.load("scenarios.json");
            world->go_to_next_level(); // Start first level
            m_main_map_controller.set_game_world(*world);

            m_main_map_controller.show();
        }

        void menu_controller::load() {
            m_load_controller.show();
        }

        void menu_controller::quit() {
            m_engine.stop();
        }

        void menu_controller::credits() {
            m_credits_controller.show();
        }
    }
}
