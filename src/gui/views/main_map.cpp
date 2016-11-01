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

        void main_map::set_map_model(models::main_map_model *main_map_model) {
            m_view_model = main_map_model;
        }

        void main_map::before_first_draw() {
            m_texture_manager.load("images/grass.png", "grass_1");
            m_texture_manager.load("images/building.png", "building_1");
            engine::eventbus::eventbus<engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT>>::get_instance().subscribe(this);
        }

        void main_map::draw() {
            // The position for the next tile
            float x = m_view_model->map->min.x;
            float y = m_view_model->map->min.y;

            for (size_t i = 0; i < m_view_model->tiles.size(); i++) {
                if (i != 0) {
                    x = m_view_model->map->min.x;
                    y = m_view_model->map->min.y + (m_view_model->tile_height * i);
                }

                for (auto tile : m_view_model->tiles[i]) {
                    // Create tile box
                    engine::math::box2_t tile_box({x, y}, {x + m_view_model->tile_width, y + m_view_model->tile_height});

                    // Let the tile draw
                    tile->draw(m_texture_manager, tile_box);

                    x += m_view_model->tile_width;
                }
            }
        }

        void main_map::after_last_draw() {
            m_texture_manager.unload("grass_1");
            m_texture_manager.unload("building_1");

            engine::eventbus::eventbus<engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT>>::get_instance().unsubscribe(this);
        }

        void main_map::on_event(engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT> &event) {
            engine::math::vec2_t *position = engine::input::input_handler::get_instance()->get_mouse_position();

            // Check if the position is on the map
            if (m_view_model->map->contains(*position)) {
                gui::router::get_instance().use_and_perform("click_tile");
            }
        }
    }
}
