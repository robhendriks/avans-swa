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


namespace gui {
    namespace controllers {
        class main_map_controller;
    }
}

namespace gui {
    namespace views {
        class main_map
            : public base_view,
              engine::eventbus::subscriber<engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT>> {
        public:
            main_map(engine::graphics::texture_manager &texture_manager, engine::audio::music_manager &music_manager,
                     engine::window &window, models::main_map_model &model);

            void set_controller(controllers::main_map_controller &controller);

            void before();

            void draw(float interpolation);

            void after();

            void on_event(engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT> &event);

        private:
            engine::graphics::texture_manager &m_texture_manager;
            engine::audio::music_manager &m_music_manager;
            engine::window &m_window;
            models::main_map_model &m_model;
            controllers::main_map_controller *m_controller;
        };
    }
}
#endif //CITY_DEFENCE_MAIN_MAP_H
