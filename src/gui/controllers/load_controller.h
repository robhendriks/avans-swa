//
// Created by robbie on 9-1-2017.
//

#ifndef CITY_DEFENCE_LOAD_CONTROLLER_H
#define CITY_DEFENCE_LOAD_CONTROLLER_H

#include "base_controller.h"
#include "../views/load.h"
#include "../../data/json/save_games_json_repository.h"
#include "../models/load_model.h"
#include "../../services/world_loader/base_world_loader.h"
#include "main_map_controller.h"

namespace gui {
    namespace views {
        class load;
    }

    namespace controllers {
        class main_map_controller;
    }
}

namespace gui {
    namespace controllers {
        class load_controller : public base_controller {
        public:
            load_controller(views::load &view, models::load_model &model, main_map_controller &main_map_controller,
                            game &game1, data::json::save_games_json_repository &games_repository,
                            services::world_loader::base_world_loader &world_loader);

            void show();

            void load(std::string file);

        private:
            views::load &m_view;
            models::load_model &m_model;
            main_map_controller &m_main_map_controller;
            data::json::save_games_json_repository &m_games_repository;
            services::world_loader::base_world_loader &m_world_loader;
        };
    }
}


#endif //CITY_DEFENCE_LOAD_CONTROLLER_H
