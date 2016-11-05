//
// Created by te on 01-Nov-16.
//

#include "main_map_controller.h"
#include "../../domain/buildings/building.h"

namespace gui {
    namespace controllers {

        main_map_controller::main_map_controller(views::main_map &view, models::main_map_model &model, game &game1) :
            base_controller(game1), m_view(view), m_model(model) {

            view.set_controller(*this);

            // This code should be placed somewhere else
            m_model.tile_height = 32;
            m_model.tile_width = 32;
            auto *domain_map = new domain::map::map(10, 10);
            m_model.tiles = domain_map->get_fields();
            engine::math::box2_t *map = new engine::math::box2_t({{0, 0}, {(float) (10 * m_model.tile_width), (float) (10 * m_model.tile_height)}});
            m_model.map = map;
        }

        void main_map_controller::show() {
            // Draw the view
            view(m_view);
        }

        void main_map_controller::tile_click(domain::map::base_field &tile) {
            domain::buildings::building building;
            tile.place(building);

            show();
        }
    }
}
