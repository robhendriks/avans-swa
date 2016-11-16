//
// Created by te on 01-Nov-16.
//

#include "main_map.h"
#include "../../engine/input/input_handler.h"
#include "../../engine/eventbus/eventbus.h"
namespace gui {
    namespace views {

        main_map::main_map(engine::graphics::texture_manager &texture_manager, engine::audio::music_manager &music_manager,
                           engine::window &window, models::main_map_model &model)
            : m_texture_manager(texture_manager), m_music_manager(music_manager), m_window(window), m_model(model) {
        }

        void main_map::before() {
            m_music_manager.load("sounds/game.mp3", "game_bg_music");
            m_music_manager.play("game_bg_music");

            engine::eventbus::eventbus::get_instance().subscribe(this);
        }

        void main_map::draw(float interpolation) {
            // Draw the map in the middle of the screen
            auto win_box = m_window.get_display_box();
            m_model.map_box->to_left(win_box);
            m_model.map_box->to_top(win_box);
            m_model.map_box->to_center(win_box);

            m_model.world->draw(m_texture_manager, *m_model.map_box);
        }

        void main_map::after() {
            // can be done by the objects as well
            m_model.world->unload(m_texture_manager);
            m_music_manager.unload("game_bg_music");

            engine::eventbus::eventbus::get_instance().unsubscribe(this);
        }

        void main_map::on_event(engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT> &event) {
            engine::math::vec2_t *position = engine::input::input_handler::get_instance()->get_mouse_position();

            // Check if the position is on the map
            if (m_model.map_box->contains(*position)) {
                // Calculate which tile
                int col = (int) (position->x - m_model.map_box->min.x) / m_model.world->get_current_map()->get_tile_width();
                int row = (int) (position->y - m_model.map_box->min.y) / m_model.world->get_current_map()->get_tile_height();

                for(std::shared_ptr<domain::map::base_field> tile : m_model.world->get_current_map()->get_fields()){
                    if(tile->get_y() == row && tile->get_x() == col){
                        m_controller->tile_click(*tile);
                        break;
                    }
                }
            }
        }

        void main_map::set_controller(controllers::main_map_controller &controller) {
            m_controller = &controller;
        }
    }
}
