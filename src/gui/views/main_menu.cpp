//
// Created by te on 25-Oct-16.
//
#include "main_menu.h"
#include "../../engine/input/input_handler.h"
#include "../../router.h"

namespace gui {
    namespace views {
        main_menu::main_menu(engine::texture::texture_manager &texture_manager) : m_texture_manager(texture_manager) {
        }

        void main_menu::draw() {
            m_texture_manager.load_texture("images/menu.png", "menu_item_1");
            m_texture_manager.draw("menu_item_1", 0, 0, 339, 122, 150, 0);
            m_texture_manager.draw("menu_item_1", 0, 122, 339, 122, 150, 122);
            m_texture_manager.draw("menu_item_1", 0, 244, 339, 122, 150, 244);
        }

        void main_menu::on_event(engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT> &event) {
            engine::math::vec2_t *position = engine::input::input_handler::get_instance()->get_mouse_position();
            if (position->x >= 150 && position->x <= 150 + 339) {
                if (position->y >= 0 && position->y < 122) {
                    SDL_Log("PLAY");
                } else if (position->y >= 122 && position->y < 244) {
                    SDL_Log("LOAD");
                } else if (position->y < 366){
                    router::get_instance().use_and_perform("quit");
                }
            }
        }
    }
}
