//
// Created by te on 01-Nov-16.
//

#include "main_map_controller.h"
#include "../../domain/buildings/building.h"
#include "menu_controller.h"

namespace gui {
    namespace controllers {
        main_map_controller::main_map_controller(views::main_map &view, engine::engine &engine, views::win_game_over& transition_view, models::main_map_model &model, models::transition_level_model& transition_model, game &game1) :
            base_controller(game1), m_view(view), m_trans_view(transition_view), m_engine(engine), m_model(model), m_trans_model(transition_model) {
            view.set_controller(*this);
            transition_view.set_controller(this);
            m_model.map_box = {};
        }

        void main_map_controller::show() {
            std::shared_ptr<domain::game_level::game_level> lvl = m_model.world->get_current_level();
            if(lvl->get_start_time() == 0)
                lvl->set_start_time((long) m_engine.get_time_elapsed());

            bool game_over = lvl->is_game_over((long) m_engine.get_time_elapsed());
            bool goal_reached = lvl->is_goal_reached();
            if(game_over || goal_reached){
                m_trans_model.stats_lvl = lvl->get_stats();
                m_trans_model.stats_game = std::shared_ptr<domain::game_level::game_stats>(new domain::game_level::game_stats(m_model.world->get_stats()));
                m_trans_model.result = !game_over;
                m_trans_model.next_lvl_exists = m_model.world->is_next_level();
                view(m_trans_view);
            }
            else
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
            int width = this->m_model.world->get_current_level()->get_map()->get_width();
            int height = this->m_model.world->get_current_level()->get_map()->get_height();
            engine::math::box2_t *map_box = new engine::math::box2_t({{0, 0}, {(float) (width), (float) (height)}});
            m_model.map_box = map_box;
        }

        domain::gameworld::game_world main_map_controller::get_game_world() {
            return *m_model.world;
        }

        void main_map_controller::next_lvl() {
           if(m_model.world->is_next_level()){
               m_model.world->next_level();
               show();
           }
           else
               m_menu_controller->show();
        }

        void main_map_controller::set_menu_controller(std::shared_ptr<gui::controllers::menu_controller> menu_controller) {
            m_menu_controller = menu_controller;
        }
    }
}
