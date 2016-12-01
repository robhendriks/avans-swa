//
// Created by te on 25-Oct-16.
//

#include "main_menu.h"

namespace gui {
    namespace views {
        main_menu::main_menu(top_bar &top_bar1, engine::audio::music_manager &music_manager) : m_top_bar(top_bar1),
                                                                            m_music_manager(music_manager),
                                                                            m_play_dest({{150, 0},
                                                                                         {489, 122}}),
                                                                            m_load_dest({{150, 122},
                                                                                         {489, 244}}),
                                                                            m_quit_dest({{150, 244},
                                                                                         {489, 366}}) {
        }

        void main_menu::on_display_change(engine::math::box2_t display_box) {
            m_top_bar.on_display_change(display_box);
        }

        void main_menu::draw(unsigned int time_elapsed, engine::math::box2_t display_box) {
            m_top_bar.draw(time_elapsed, display_box);

            m_top_bar.m_texture_manager.draw("menu_item_1", {0, 0}, m_play_dest);
            m_top_bar.m_texture_manager.draw("menu_item_1", {0, 122}, m_load_dest);
            m_top_bar.m_texture_manager.draw("menu_item_1", {0, 244}, m_quit_dest);
        }

        void main_menu::on_event(engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT> &event) {
            engine::math::vec2_t *position = engine::input::input_handler::get_instance()->get_mouse_position();

            if (m_play_dest.contains(*position)) {
                m_top_bar.m_menu_controller->play();
            } else if (m_load_dest.contains(*position)) {
                m_top_bar.m_menu_controller->load();
            } else if (m_quit_dest.contains(*position)) {
                m_top_bar.m_menu_controller->quit();
            } else {
                m_top_bar.m_menu_controller->credits();
            }
        }

        void main_menu::before() {
            m_top_bar.before();

            m_top_bar.m_texture_manager.load("images/menu.png", "menu_item_1");
            m_music_manager.load("sounds/menu.wav", "menu_bg_music");
            m_music_manager.play("menu_bg_music");

            engine::eventbus::eventbus::get_instance().subscribe(this);
        }

        void main_menu::after() {
            m_top_bar.after();

            m_top_bar.m_texture_manager.unload("menu_item_1");
            m_music_manager.unload("menu_bg_music");

            engine::eventbus::eventbus::get_instance().unsubscribe(this);
        }

        void main_menu::set_controller(std::shared_ptr<controllers::menu_controller> menu_controller) {
            m_top_bar.set_controller(menu_controller);
        }
    }
}
