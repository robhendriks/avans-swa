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
            m_model.map->to_left(win_box);
            m_model.map->to_top(win_box);
            m_model.map->to_center(win_box);

            // The position for the next tile
            float x = m_model.map->min.x;
            float y = m_model.map->min.y;

            for (size_t i = 0; i < m_model.tiles.size(); i++) {
                if (i != 0) {
                    x = m_model.map->min.x;
                    y = m_model.map->min.y + (m_model.tile_height * i);
                }

                for (auto tile : m_model.tiles[i]) {
                    // Create tile box
                    engine::math::box2_t tile_box({x, y}, {x + m_model.tile_width, y + m_model.tile_height});

                    // Let the tile draw
                    try{
                    tile->draw(m_texture_manager, tile_box);
                    }
                    catch(std::exception e){
                        e.what();
                    }
                    x += m_model.tile_width;
                }
            }
        }

        void main_map::after() {
            // can be done by the objects as well
            m_texture_manager.unload("grass_1");
            m_texture_manager.unload("building_1");

            m_music_manager.unload("game_bg_music");

            engine::eventbus::eventbus::get_instance().unsubscribe(this);
        }

        void main_map::on_event(engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT> &event) {
            engine::math::vec2_t *position = engine::input::input_handler::get_instance()->get_mouse_position();

            // Check if the position is on the map
            if (m_model.map->contains(*position)) {
                // Calculate which tile
                int col = (int) ((position->x - m_model.map->min.x) / m_model.tile_width);
                int row = (int) ((position->y - m_model.map->min.y) / m_model.tile_height);
                m_controller->tile_click(*m_model.tiles[row][col]);
            }
        }

        void main_map::set_controller(controllers::main_map_controller &controller) {
            m_controller = &controller;
        }
    }
}
