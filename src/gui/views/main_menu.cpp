//
// Created by te on 25-Oct-16.
//
#include "main_menu.h"
#include "../../engine/input/input_handler.h"
#include "../../engine/eventbus/eventbus.h"

namespace gui {
    namespace views {
        main_menu::main_menu(engine::graphics::texture_manager &texture_manager) : m_texture_manager(texture_manager),
                                                                                   m_play_dest({{150, 0},
                                                                                                {489, 122}}),
                                                                                   m_load_dest({{150, 122},
                                                                                                {489, 244}}),
                                                                                   m_quit_dest({{150, 244},
                                                                                                {489, 366}}) {
        }

        void main_menu::draw() {
            m_texture_manager.draw("menu_item_1", {0, 0}, m_play_dest);
            m_texture_manager.draw("menu_item_1", {0, 122}, m_load_dest);
            m_texture_manager.draw("menu_item_1", {0, 244}, m_quit_dest);
        }

        void main_menu::on_event(engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT> &event) {
            engine::math::vec2_t *position = engine::input::input_handler::get_instance()->get_mouse_position();

            if (m_play_dest.contains(*position)) {
                m_menu_controller->play();
            } else if (m_load_dest.contains(*position)) {
                SDL_Log("LOAD MENU BUTTON");
            } else if (m_quit_dest.contains(*position)) {
                m_menu_controller->quit();
            }
        }

        void main_menu::before() {
            m_texture_manager.load("images/menu.png", "menu_item_1");
            engine::eventbus::eventbus::get_instance().subscribe(this);
        }

        void main_menu::after() {
            m_texture_manager.unload("menu_item_1");
            engine::eventbus::eventbus::get_instance().unsubscribe(this);
        }

        void main_menu::set_controller(controllers::menu_controller &menu_controller) {
            m_menu_controller = &menu_controller;
        }
    }
}
