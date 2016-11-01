//
// Created by te on 01-Nov-16.
//

#include "main_map.h"
#include "../../engine/input/input_handler.h"
#include "../router.h"
#include "../../engine/eventbus/eventbus.h"

namespace gui {
    namespace views {


        main_map::main_map(engine::texture::texture_manager &texture_manager)  : _texture_manager(texture_manager),
             m_play_dest({{150, 0}, {489, 122}}){
        }

        void main_map::set_game_world(domain::gameworld::game_world game_world) {

        }

        void main_map::before_first_draw() {
            _texture_manager.load("images/menu.png", "menu_item_1");
            engine::eventbus::eventbus<engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT>>::get_instance().subscribe(this);
        }

        void main_map::draw() {
            _texture_manager.draw("menu_item_1", {0, 0}, m_play_dest);
        }

        void main_map::after_last_draw() {
            _texture_manager.unload("menu_item_1");
            engine::eventbus::eventbus<engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT>>::get_instance().unsubscribe(this);
        }

        void main_map::on_event(engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT> &event) {
            SDL_Log("PLAY");
        }
    }
}