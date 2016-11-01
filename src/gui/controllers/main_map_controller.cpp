//
// Created by te on 01-Nov-16.
//

#include "main_map_controller.h"
#include "../../domain/map/passable_field.h"
#include "../../domain/buildings/building.h"
#include "../../engine/input/input_handler.h"
#include "../router.h"

namespace gui {
    namespace controllers {

        main_map_controller::main_map_controller(engine::window &window) : m_window(window), m_map(new domain::map::map(10, 10)) {

        }

        void main_map_controller::show(int call, views::main_map &view) {
            if (call > 0) {
                // Last call, unsubscribe
                view.after_last_draw();
            } else {
                if (call < 0) {
                    // First call, subscribe on eventbus
                    view.before_first_draw();
                } else {
                    delete m_main_map_model;
                }

                m_main_map_model = new models::main_map_model();
                m_main_map_model->tile_height = 32;
                m_main_map_model->tile_width = 32;
                m_main_map_model->tiles = m_map->get_fields();
                // Create map and place it in the middle of the screen
                engine::math::box2_t *map = new engine::math::box2_t({{0, 0}, {(float)(10 * m_main_map_model->tile_width), (float)(10 * m_main_map_model->tile_height)}});
                map->to_center(m_window.get_display_box());

                m_main_map_model->map = map;

                // Draw the view
                view.set_map_model(m_main_map_model);
                view.draw();
            }
        }

        void main_map_controller::click_tile(int call) {
            if (call == -1) {
                engine::math::vec2_t *position = engine::input::input_handler::get_instance()->get_mouse_position();

                // Check which tile is clicked
                int col = (int)((position->x - m_main_map_model->map->min.x) / m_main_map_model->tile_width);
                int row = (int)((position->y - m_main_map_model->map->min.y) / m_main_map_model->tile_height);
                domain::map::base_field *p = m_main_map_model->tiles[row][col];

                domain::buildings::building building;
                p->place(building);

                delete m_main_map_model;
                router::get_instance().go_back();
            }
        }

        main_map_controller::~main_map_controller() {
            delete m_map;
        }
    }
}
