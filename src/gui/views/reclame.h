//
// Created by Leendert on 21-12-2016.
//

#ifndef CITY_DEFENCE_RECLAME_H
#define CITY_DEFENCE_RECLAME_H

#include "../../domain/drawable/draw_managers_wrapper.h"
#include "base_view.h"
#include "../../engine/input/mouse_buttons.h"
#include "../../engine/events/mouse_button_down.h"
#include "help.h"

namespace gui {
    namespace views {
        class help;
    }
}

namespace gui {
    namespace views {
        class reclame : public base_view,
                     engine::eventbus::subscriber<engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT>>,
                     engine::eventbus::subscriber<engine::events::key_down> {
            friend class in_game_menu;
            friend class level;
            friend class win_game_over;
            friend class main_menu;
        public:
            reclame(help &help_view);

            void set_image(std::string image);

            void toggle_show();

            void before();

            void on_display_change(engine::math::box2_t display_box);

            void draw(unsigned int time_elapsed, engine::math::box2_t display_box);

            void after();

            void on_event(engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT> &event);

            void on_event(engine::events::key_down &event);

            void call_on_show_change(std::function<void(bool)> callback);

        private:

            help &m_help_view;
            engine::graphics::texture_manager &m_texture_manager;
            std::string m_reclame_image;
            bool m_show;
            bool m_reclame_loaded;
            std::unique_ptr<engine::math::box2_t> m_overlay_box;
            std::unique_ptr<engine::math::box2_t> m_reclame_box;
            std::unique_ptr<engine::math::box2_t> m_image_box;
            std::unique_ptr<engine::math::box2_t> m_cross_circle_box;
            std::unique_ptr<engine::math::box2_t> m_cross_box;
            std::vector<std::function<void(bool)>> m_callbacks;
        };
    }
}
#endif //CITY_DEFENCE_RECLAME_H
