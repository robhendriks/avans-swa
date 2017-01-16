//
// Created by robbie on 9-1-2017.
//

#include "load_controller.h"

namespace gui {
    namespace controllers {

        load_controller::load_controller(views::load &view, models::load_model &model,
                                         main_map_controller &main_map_controller, game &game1,
                                         data::json::save_games_json_repository &games_repository,
                                         services::world_loader::base_world_loader &world_loader) :
            base_controller(game1), m_view(view), m_model(model), m_main_map_controller(main_map_controller),
            m_games_repository(games_repository), m_world_loader(world_loader) {

            m_view.set_load_controller(*this);
        }

        void load_controller::show() {
            m_games_repository.load();
            m_model.saved_games = m_games_repository.all();

            // Show view
            view(m_view);
        }

        void load_controller::load(std::string file) {
            domain::gameworld::game_world *world = m_world_loader.load(file);
            world->go_to_next_level();

            m_main_map_controller.set_game_world(*world);
            m_main_map_controller.show();
        }
    }
}
