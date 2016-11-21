//
// Created by te on 19-Nov-16.
//

#ifndef CITY_DEFENCE_WIN_GAME_OVER_H
#define CITY_DEFENCE_WIN_GAME_OVER_H

#include "base_view.h"
#include "../../engine/graphics/texture_manager.h"
#include "../../engine/graphics/font_manager.h"
#include "../../engine/graphics/color_manager.h"
#include "../../engine/window.h"
#include "../../engine/engine.h"
#include "../controllers/main_map_controller.h"
#include "../models/transition_level_model.h"
#include <memory>

// ik snap niet hoe main_map_controller dit kan include en dit weer main_map_controller. snap ook het niet van deze forward decl als ik de .h toch al heb geinclude hier
// in visual studio werkt dit niet namelijk :(
namespace gui{
    namespace controllers{
        class main_map_controller;
    }
}

namespace gui {
    namespace views {
        class win_game_over : public base_view, engine::eventbus::subscriber<engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT>>{
        public:
            win_game_over(engine::graphics::texture_manager &texture_manager, engine::graphics::font_manager &font_manager,
                    engine::graphics::color_manager &color_manager, engine::window &window, engine::engine &engine1,
            engine::audio::music_manager &music_manager, models::transition_level_model &model);
            void before();
            void after();
            void draw(float interpolation);
            void on_event(engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT> &event);
            void set_controller(gui::controllers::main_map_controller* controller);
            ~win_game_over();
        private:
            engine::graphics::texture_manager &m_texture_manager;
            engine::graphics::font_manager &m_font_manager;
            engine::graphics::color_manager &m_color_manager;
            engine::audio::music_manager &m_music_manager;
            engine::window &m_window;
            engine::engine &m_engine;
            gui::controllers::main_map_controller* m_controller;
            models::transition_level_model& m_model;
            engine::math::box2_t* m_title_box;
            engine::math::box2_t* m_header_box;
            engine::math::box2_t* m_statistics_box;
            engine::math::box2_t* m_continue_box;
        };
    }
}

#endif //CITY_DEFENCE_WIN_GAME_OVER_H
