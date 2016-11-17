//
// Created by te on 01-Nov-16.
//

#include "main_map_controller.h"
#include "../../domain/buildings/building.h"
#include <memory>

namespace gui {
    namespace controllers {

        main_map_controller::main_map_controller(views::main_map &view, models::main_map_model &model, game &game1) :
            base_controller(game1), m_view(view), m_model(model) {
            view.set_controller(*this);
            m_model.map_box = {};
        }



        void main_map_controller::show() {
            // Draw the view
            view(m_view);
        }

        void main_map_controller::tile_click(domain::map::base_field &tile) {
            engine::math::vec2_t* t = new engine::math::vec2_t(0,0);
            domain::buildings::building* building =  new domain::buildings::building("building_1", "images/building.png", t, 0);
            tile.place(building);
            show();
        }

        void main_map_controller::set_game_world(std::unique_ptr<domain::gameworld::game_world>&& game_world) {
            this->m_model.world = std::move(game_world);
            engine::math::box2_t *map_box = new engine::math::box2_t({{0, 0}, {(float) (10 * this->m_model.world->get_current_level()->get_map()->get_tile_width()), (float) (10 * this->m_model.world->get_current_level()->get_map()->get_tile_height())}});
            m_model.map_box = map_box;

        }
    }
}
