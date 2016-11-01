//
// Created by te on 01-Nov-16.
//

#include "main_map.h"
#include "../../engine/input/input_handler.h"
#include "../router.h"
#include "../../engine/eventbus/eventbus.h"

namespace gui {
    namespace views {

        main_map::main_map(engine::graphics::texture_manager &texture_manager, engine::window &window) : m_texture_manager(texture_manager),
             m_window(window) {
        }

        void main_map::before_first_draw() {
            engine::eventbus::eventbus<engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT>>::get_instance().subscribe(this);
        }

        void main_map::draw(models::main_map_model &view_model) {
            // Create map and place it in the middle of the screen
            engine::math::box2_t map({{0, 0}, {static_cast<float>(view_model.number_of_tiles * view_model.tile_width), static_cast<float>(view_model.number_of_tiles * view_model.tile_height)}});
            map.to_center(m_window.get_display_box());

            // The position for the next tile
            engine::math::vec2_t tile_pos({0, 0});

            for (int i = 0; i < view_model.number_of_tiles; i++) {
                if (i != 0) {
                    tile_pos.x = 0;
                    tile_pos.y = view_model.tile_height * i;
                }

                for (auto tile : view_model.tiles[0]) {
                    // Create tile box
                    engine::math::box2_t tile_box({0, 0}, {static_cast<float>(view_model.tile_width), static_cast<float>(view_model.tile_height)});
                    // Place the tile on the correct position
                    tile_box.move_to_start(tile_pos);

                    tile_pos.x += view_model.tile_width;
                }
            }
        }

        void main_map::after_last_draw() {
            engine::eventbus::eventbus<engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT>>::get_instance().unsubscribe(this);
        }

        void main_map::on_event(engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT> &event) {
            SDL_Log("PLAY");
        }
    }
}
