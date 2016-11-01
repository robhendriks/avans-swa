//
// Created by te on 01-Nov-16.
//

#ifndef CITY_DEFENCE_MAIN_MAP_H
#define CITY_DEFENCE_MAIN_MAP_H

#include "../../engine/graphics/texture_manager.h"
#include "../../engine/events/mouse_button_down.h"
#include "../../engine/eventbus/subscriber.h"
#include "../../domain/gameworld/game_world.h"

namespace gui {
    namespace views {
        class main_map : public engine::eventbus::subscriber<engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT>>{
        public:
            main_map(engine::graphics::texture_manager &texture_manager);

            void set_game_world(domain::gameworld::game_world game_world);

            void before_first_draw();

            void draw();

            void after_last_draw();

            void on_event(engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT> &event);
        private:
            domain::gameworld::game_world _game_world;
            engine::graphics::texture_manager& _texture_manager;

            engine::math::box2_t m_play_dest;
        };
    }
}
#endif //CITY_DEFENCE_MAIN_MAP_H
