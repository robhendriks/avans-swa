//
// Created by robbie on 29-10-2016.
//

#include "menu_controller.h"

namespace gui {
    namespace controllers {

        menu_controller::menu_controller(views::main_menu &main_menu, engine::engine &engine,
                                         controllers::main_map_controller &main_map_controller,
                                         controllers::credits_controller &credits_controller, game &game1,
                                         services::level_loader::base_level_loader &level_loader)
            : base_controller(game1), m_engine(engine), m_main_menu(main_menu),
              m_main_map_controller(main_map_controller), m_credits_controller(credits_controller),
              m_level_loader(level_loader) {

            main_map_controller.set_menu_controller(std::shared_ptr<menu_controller>(this));
            m_main_menu.set_controller(std::shared_ptr<menu_controller>(this));
        }

        void menu_controller::show() {
            view(m_main_menu);
        }

        void menu_controller::play() {
            auto first_level = m_level_loader.load(0);
            m_main_map_controller.set_game_world(std::unique_ptr<domain::gameworld::game_world>(new domain::gameworld::game_world(std::move(first_level))));
            m_main_map_controller.show();
        }

        void menu_controller::load() {
            play();
        }

        void menu_controller::quit() {
            m_engine.stop();
        }

        void menu_controller::credits() {
            m_credits_controller.show();
        };
    }
}
