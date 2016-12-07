//
// Created by te on 01-Nov-16.
//

#ifndef CITY_DEFENCE_MAIN_MAP_H
#define CITY_DEFENCE_MAIN_MAP_H

#include "../../engine/graphics/texture_manager.h"
#include "../../engine/events/mouse_button_down.h"
#include "../../engine/eventbus/subscriber.h"
#include "../../domain/gameworld/game_world.h"
#include "../../engine/window.h"
#include "../models/main_map_model.h"
#include "base_view.h"
#include "../controllers/main_map_controller.h"
#include "../../engine/audio/music_manager.h"
#include "../../engine/audio/sound_manager.h"
#include "../../engine/input/keycodes.h"
#include "../../engine/events/key_down.h"
#include "level_goals.h"
#include "../../events/goal_reached.h"


namespace gui {
    namespace controllers {
        class main_map_controller;
    }
}

namespace gui {
    namespace views {
        class level : public base_view,
                      engine::eventbus::subscriber<engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT>>,
                      engine::eventbus::subscriber<engine::events::key_down>,
                      engine::eventbus::subscriber<events::goal_reached> {
        public:

            level(in_game_menu &in_game_menu1, level_goals &goals_view, engine::audio::music_manager &music_manager,
                  engine::window &window, models::main_map_model &model, engine::audio::sound_manager &sound_manager);

            void set_controller(controllers::main_map_controller &controller);

            void before();

            void on_display_change(engine::math::box2_t display_box);

            void draw(unsigned int time_elapsed, engine::math::box2_t display_box);

            void after();

            void on_event(engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT> &event);

            void on_event(engine::events::key_down &event);

            void on_event(events::goal_reached &event);

            void on_pause();
        private:
            void update_placeable_objects_page();

            void navigate_left();

            void navigate_right();

            in_game_menu &m_in_game_menu;
            level_goals &m_goals_view;
            engine::audio::music_manager &m_music_manager;
            engine::window &m_window;
            models::main_map_model &m_model;
            engine::audio::sound_manager &m_sound_manager;
            std::unique_ptr<engine::math::box2_t> m_placeable_objects_box;
            std::unique_ptr<engine::math::box2_t> m_arrow_left_box;
            std::unique_ptr<engine::math::box2_t> m_arrow_right_box;
            std::unique_ptr<engine::math::box2_t> m_countdown_box;
            std::unique_ptr<engine::math::box2_t> m_pause_box;
            std::unique_ptr<engine::math::box2_t> m_overlay_box;
            std::unique_ptr<engine::math::box2_t> m_overlay_resume_box;
            controllers::main_map_controller *m_controller;
            int m_pages;
            int m_current_page;
            int m_objects_per_page;
        };
    }
}
#endif //CITY_DEFENCE_MAIN_MAP_H
