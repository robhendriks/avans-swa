//
// Created by te on 01-Nov-16.
//

#ifndef CITY_DEFENCE_MAIN_MAP_CONTROLLER_H
#define CITY_DEFENCE_MAIN_MAP_CONTROLLER_H

#include <fstream>
#include <json.hpp>

#include "../views/main_map.h"
#include "../models/transition_level_model.h"
#include "../../domain/map/map.h"
#include "base_controller.h"
#include "../views/win_game_over.h"

namespace gui {
    namespace views {
        class main_map;
        class win_game_over;
    }
}

namespace gui {
    namespace controllers {
        class menu_controller;

        class main_map_controller : public base_controller {
        public:
            main_map_controller(views::main_map &view, views::win_game_over& transition_view, models::main_map_model &model, models::transition_level_model& transition_model, game &game1);
            void show();
            void tile_click(domain::map::base_field &tile);
            void set_game_world(std::unique_ptr<domain::gameworld::game_world>&& game_world);
            void set_menu_controller(std::shared_ptr<gui::controllers::menu_controller> menu_controller);
            domain::gameworld::game_world get_game_world();
            void next_lvl();
        private:
            std::shared_ptr<gui::controllers::menu_controller> m_menu_controller;

            views::main_map &m_view;
            views::win_game_over& m_trans_view;

            models::main_map_model &m_model;
            models::transition_level_model& m_trans_model;
        };
    }
}

#endif //CITY_DEFENCE_MAIN_MAP_CONTROLLER_H
