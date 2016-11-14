//
// Created by te on 01-Nov-16.
//

#ifndef CITY_DEFENCE_MAIN_MAP_CONTROLLER_H
#define CITY_DEFENCE_MAIN_MAP_CONTROLLER_H

#include <fstream>
#include <json.hpp>

#include "../views/main_map.h"
#include "../../domain/map/map.h"
#include "base_controller.h"

using json = nlohmann::json;

namespace gui {
    namespace views {
        class main_map;
    }
}

namespace gui {
    namespace controllers {
        class main_map_controller : public base_controller {
        public:
            main_map_controller(views::main_map &view, models::main_map_model &model, game &game1);

            void load(const char *filename);

            void load_tiles(json &root, models::main_map_model &map_model);

            void load_objects(json &root, models::main_map_model &map_model);

            void show();

            void tile_click(domain::map::base_field &tile);

        private:
            views::main_map &m_view;
            models::main_map_model &m_model;
        };
    }
}

#endif //CITY_DEFENCE_MAIN_MAP_CONTROLLER_H
