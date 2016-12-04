//
// Created by te on 01-Nov-16.
//

#include "main_map_controller.h"
#include "../controllers/menu_controller.h"

namespace gui {
    namespace controllers {
        main_map_controller::main_map_controller(views::level &view, engine::engine &engine,
                                                 views::win_game_over &transition_view, models::main_map_model &model,
                                                 models::transition_level_model &transition_model, game &game1,
                                                 services::wave::wave_management &wave_management) :
            base_controller(game1), m_view(view), m_trans_view(transition_view), m_engine(engine), m_model(model),
            m_trans_model(transition_model), m_wave_management_service(wave_management) {

            m_view.set_controller(*this);
            m_trans_view.set_controller(*this);
        }

        void main_map_controller::show() {
            auto &lvl = m_model.world->get_current_level();
            if (lvl.get_start_time() == 0)
                lvl.set_start_time(m_engine.get_time_elapsed());

            if (is_lvl_done()) {
                m_trans_model.stats_lvl = lvl.get_stats();
                m_trans_model.stats_game = std::shared_ptr<domain::game_level::game_stats>(
                    new domain::game_level::game_stats(m_model.world->get_stats()));
                m_trans_model.result = !lvl.is_game_over(m_engine.get_time_elapsed());
                m_trans_model.next_lvl_exists = m_model.world->has_next_level();

                view(m_trans_view);
            } else {
                view(m_view);
            }
        }

        bool main_map_controller::is_lvl_done() {
            auto &lvl = m_model.world->get_current_level();

            bool game_over = lvl.is_game_over(m_engine.get_time_elapsed());
            bool goal_reached = lvl.is_goal_reached();

            return game_over || goal_reached;
        }

        // this needs to be handled by eventbus
        void main_map_controller::update() {
            auto current_enemies = m_model.world->get_current_level().get_enemies_in_lvl();
            for (auto enemy : m_wave_management_service.get_enemies(m_engine.get_time_elapsed())) {
                current_enemies.push_back(enemy);
            }
            //Updates resources
            m_model.world->get_current_level().set_enemies_in_lvl(current_enemies);
           for(auto&x:m_model.world->get_current_level().get_map()->get_fields_with_objects()){
               //TODO get the proper building which is not really possible now
                x->get_object()->get_field()->get_max_row();
               m_model.world->get_current_level().get_resources()[0]->increment_resource(1);

               };

        }


        void main_map_controller::set_game_world(std::unique_ptr<domain::gameworld::game_world> &&game_world) {
            m_model.world = std::move(game_world);

            auto lvl = m_model.world->get_current_level();
            // set wave service values to first lvl
            set_settings_wave_management_service(lvl);
        }

        domain::gameworld::game_world main_map_controller::get_game_world() {
            return *m_model.world;
        }

        void main_map_controller::next_lvl() {
            m_wave_management_service.reset();

            if (m_model.world->has_next_level()) {
                m_model.world->next_level();
                // set wave service values to next lvl
                set_settings_wave_management_service(m_model.world->get_current_level());
                show();
            } else {
                m_menu_controller->show();
            }
        }

        void
        main_map_controller::set_menu_controller(std::shared_ptr<gui::controllers::menu_controller> menu_controller) {
            m_menu_controller = menu_controller;
        }

        void main_map_controller::set_settings_wave_management_service(domain::game_level::game_level lvl) {
            m_wave_management_service.set_peace_period(lvl.get_peace_period());
            m_wave_management_service.set_base_wave_opportunity(lvl.get_base_wave_base_opportunity());
            m_wave_management_service.set_wave_opportunity_increase(lvl.get_wave_opportunity_increase());
            m_wave_management_service.set_wave_spawn_time_range(lvl.get_wave_spawn_time_range());
            m_wave_management_service.set_waves_interval(lvl.get_waves_interval());
            m_wave_management_service.set_spawn_bosses(lvl.get_spawn_bosses());
            m_wave_management_service.set_spawnable_nation(lvl.get_enemy_nation());
        }
    }
}
