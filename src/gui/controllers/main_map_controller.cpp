//
// Created by te on 01-Nov-16.
//

#include "main_map_controller.h"
#include "../../domain/gameworld/highscore.h"

namespace gui {
    namespace controllers {
        main_map_controller::main_map_controller(views::level &view, engine::engine &engine,
                                                 views::win_game_over &transition_view, models::main_map_model &model,
                                                 models::transition_level_model &transition_model,
                                                 models::level_goals_model &level_goals_model, game &game1,
                                                 services::wave::wave_management &wave_management,
                                                 data::json::highscore_json_repository &highscore_repository,
                                                 services::world_saver::base_world_saver &world_saver) :
                base_controller(game1), m_view(view), m_trans_view(transition_view), m_engine(engine), m_model(model),
                m_trans_model(transition_model), m_level_goals_model(level_goals_model),
                m_wave_management_service(wave_management),
                m_highscore_repository(highscore_repository), m_world_saver(world_saver) {
            m_view.set_controller(*this);
            m_trans_view.set_controller(*this);

            m_previous_time = 0;
        }

        void main_map_controller::show() {
            auto *lvl = m_model.world->get_current_level();

            m_level_goals_model.game_goals = &lvl->get_goal();
            m_level_goals_model.game_stats = &lvl->get_stats();

            if (lvl->get_start_time() == 0) {
                lvl->set_start_time(m_engine.get_time_elapsed());
            }

            if (is_lvl_done()) {
                lvl->transition();

                m_engine.reset_speed();
                m_model.paused = true;

                lvl->set_end_time(m_engine.get_time_elapsed());
                m_trans_model.duration = lvl->get_duration();
                m_trans_model.result = !lvl->is_game_over(m_engine.get_time_elapsed());
                m_trans_model.next_lvl_exists = m_model.world->has_next_level();

                if (!m_trans_model.result || !m_trans_model.next_lvl_exists) {
                    // Game over
                    // Create and save the score
                    domain::gameworld::highscore highscore1(m_model.world->calculate_score(), time(0));
                    m_highscore_repository.load();
                    m_highscore_repository.save(highscore1);
                    m_highscore_repository.commit();

                    // Set the highscores in the model
                    m_highscore_repository.load(); // Load again because highscore1 gets out of scope
                    m_trans_model.set_highscores(m_highscore_repository.all());
                }

                view(m_trans_view);
            } else {
                m_model.paused = false;
                view(m_view);
            }
        }

        bool main_map_controller::is_lvl_done() {
            auto *lvl = m_model.world->get_current_level();

            bool game_over = lvl->is_game_over(m_engine.get_time_elapsed());
            bool goal_reached = lvl->is_goal_reached();

            return game_over || goal_reached;
        }

        // this needs to be handled by eventbus
        void main_map_controller::update() {

            auto current_enemies = m_model.world->get_current_level()->get_enemies_in_lvl();
            for (auto &enemy : m_wave_management_service.get_enemies(m_engine.get_time_elapsed())) {
                current_enemies.push_back(enemy);
            }

            std::vector<domain::nations::enemy*> disposed;

            for (auto &enemy : current_enemies) {
                enemy->update(m_engine.get_time_elapsed());
                if (enemy->is_disposed()) {
                    disposed.push_back(enemy);
                }
            }

            for (auto &dispose : disposed) {
                m_model.world->get_current_level()->remove_enemy_in_lvl(*dispose);
            }

            auto fields = m_model.world->get_current_level()->get_map().get_fields();

            for (auto &field : fields) {
                if (!field) {
                    continue;
                }

                auto placeable_object = field->get_object();
                if (placeable_object) {
                    auto defensive_building = dynamic_cast<domain::map::objects::defensive_building*>(placeable_object);
                    if (defensive_building) {
                        defensive_building->update(*m_model.world->get_current_level(), m_engine.get_time_elapsed());
                    }
                }
            }

            m_model.world->get_current_level()->set_enemies_in_lvl(current_enemies);
            //Updates building, calles method within the level
            if (m_engine.get_time_elapsed() > m_previous_time + 500) {
                //Updating
                m_model.world->get_current_level()->update();
                m_previous_time = m_engine.get_time_elapsed();
            }
        }

        void main_map_controller::set_game_world(domain::gameworld::game_world &game_world) {
            m_model.reset();
            m_model.world = &game_world;

            // set wave service values to first lvl
            set_settings_wave_management_service(*m_model.world->get_current_level());
        }

        void main_map_controller::next_lvl() {
            m_wave_management_service.reset();

            if (m_model.world->has_next_level() && m_trans_model.result) {
                m_model.world->go_to_next_level();

                // set wave service values to next lvl
                set_settings_wave_management_service(*m_model.world->get_current_level());
                show();
            } else {
                // Game over
                m_model.reset();
                m_trans_model.reset();

                m_menu_controller->show();
            }
        }

        void main_map_controller::pause() {
            // Let the level know
            m_model.world->get_current_level()->pause();

            // Pause or resume the engine
            if (m_engine.get_state() == engine::PAUSED) {
                m_engine.resume();
                m_model.paused = false;
            } else {
                m_engine.pause();
                m_model.paused = true;
            }
        };

        void main_map_controller::save() {
            // Set played time for saving
            auto *current_level = m_model.world->get_current_level();
            int temp_played_time = current_level->get_played_time();
            current_level->set_played_time(m_engine.get_time_elapsed() - current_level->get_start_time());

            m_world_saver.save(*m_model.world);

            // Put back normal played time
            current_level->set_played_time(temp_played_time);
        }

        /**
         * Called after a level is done or stopped
         */
        void main_map_controller::resume_engine_if() {
            if (m_engine.get_state() == engine::PAUSED) {
                m_engine.resume();
            }
        }

        void main_map_controller::set_menu_controller(gui::controllers::menu_controller &menu_controller) {
            m_menu_controller = &menu_controller;
        }

        void main_map_controller::set_settings_wave_management_service(domain::game_level::game_level &lvl) {
            m_wave_management_service.set_peace_period(lvl.get_peace_period());
            m_wave_management_service.set_base_wave_opportunity(lvl.get_base_wave_base_opportunity());
            m_wave_management_service.set_wave_opportunity_increase(lvl.get_wave_opportunity_increase());
            m_wave_management_service.set_wave_spawn_time_range(lvl.get_wave_spawn_time_range());
            m_wave_management_service.set_waves_interval(lvl.get_waves_interval());
            m_wave_management_service.set_spawn_bosses(lvl.get_spawn_bosses());
            m_wave_management_service.set_spawnable_nation(lvl.get_enemy_nation());
            m_wave_management_service.get_wave_generator().get_ai().set_map(lvl.get_map());
        }
    }
}
