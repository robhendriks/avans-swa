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


namespace gui {
    namespace controllers {
        class main_map_controller;
    }
}

namespace gui {
    namespace views {
        class main_map : public base_view {
        public:

            main_map(engine::graphics::texture_manager &texture_manager, engine::audio::music_manager &music_manager,
                     engine::window &window, models::main_map_model &model, engine::audio::sound_manager &sound_manager);

            void set_controller(controllers::main_map_controller &controller);

            void before();

            void draw(unsigned int time_elapsed);

            void after();

        private:
            engine::graphics::texture_manager &m_texture_manager;
            engine::audio::music_manager &m_music_manager;
            engine::window &m_window;
            models::main_map_model &m_model;
            engine::audio::sound_manager &m_sound_manager;
            controllers::main_map_controller *m_controller;
        };
    }
}
#endif //CITY_DEFENCE_MAIN_MAP_H
