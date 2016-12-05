//
// Created by te on 01-Nov-16.
//

#ifndef CITY_DEFENCE_MAIN_MAP_CONTROLLER_H
#define CITY_DEFENCE_MAIN_MAP_CONTROLLER_H


#include "base_controller.h"
#include "../../engine/engine.h"
#include "../models/main_map_model.h"
#include "../models/transition_level_model.h"
#include "../../domain/gameworld/game_world.h"
#include "../views/level.h"
#include "../views/win_game_over.h"
#include "menu_controller.h"
#include "../../services/wave/wave_management.h"

namespace gui {
    namespace views {
        class level;

        class win_game_over;
    }

    namespace controllers {
        class menu_controller;
    }
}

namespace gui {
    namespace controllers {
        class main_map_controller : public base_controller {
        public:
            main_map_controller(views::level &view, engine::engine &engine, views::win_game_over &transition_view,
                                models::main_map_model &model, models::transition_level_model &transition_model,
                                game &game1, services::wave::wave_management &wave_management);

            void show();

            void set_game_world(std::unique_ptr<domain::gameworld::game_world> &&game_world);

            void set_menu_controller(std::shared_ptr<gui::controllers::menu_controller> menu_controller);

            domain::gameworld::game_world get_game_world();

            void next_lvl();

            bool is_lvl_done();

            void update();



        private:
            std::shared_ptr<gui::controllers::menu_controller> m_menu_controller;
            views::level &m_view;
            views::win_game_over &m_trans_view;
            engine::engine &m_engine;
            models::main_map_model &m_model;
            models::transition_level_model &m_trans_model;
            services::wave::wave_management &m_wave_management_service;
            unsigned int m_previous_time;

            // set values of the wave_management_service
            void set_settings_wave_management_service(domain::game_level::game_level lvl);
        };
    }
}

#endif //CITY_DEFENCE_MAIN_MAP_CONTROLLER_H
