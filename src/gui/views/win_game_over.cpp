//
// Created by te on 19-Nov-16.
//

#include "win_game_over.h"
#include "../../engine/graphics/box_builder.h"

namespace gui {
    namespace views {

        win_game_over::win_game_over(engine::graphics::texture_manager &texture_manager,
                                     engine::graphics::font_manager &font_manager,
                                     engine::graphics::color_manager &color_manager, engine::window &window,
                                     engine::engine &engine1, engine::audio::music_manager &music_manager, models::transition_level_model& model)  :
                m_texture_manager(texture_manager), m_font_manager(font_manager), m_color_manager(color_manager),
                m_music_manager(music_manager), m_window(window), m_engine(engine1), m_controller(nullptr), m_model(model),
                m_title_box(nullptr), m_header_box(nullptr), m_statistics_box(nullptr), m_continue_box(nullptr)
        {

        }

        void win_game_over::before() {
            engine::eventbus::eventbus::get_instance().subscribe(this);

            std::string result = m_model.result ? "Victory" : "Defeat";
            std::string last = m_model.next_lvl_exists ? "" : " - last level";
            m_texture_manager.load_text(result + last, {255, 193, 132}, *m_font_manager.get_font("roboto", 50), "w_title");

            m_texture_manager.load_text("Press the left mouse button on any part of the screen to continue.", {255, 255, 255}, *m_font_manager.get_font("roboto", 30), "continue");
        }

        void win_game_over::layout(engine::math::box2_t display_box) {
            // Create header box
            engine::graphics::box_builder builder1({display_box.width(), 100});
            builder1.as_left_top(display_box.left_top());
            m_header_box.reset(new engine::math::box2_t(builder1.build()));

            // Create title box
            engine::graphics::box_builder builder2(m_texture_manager.get_size("w_title"));
            builder2.to_center(*m_header_box);
            m_title_box.reset(new engine::math::box2_t(builder2.build()));

            // Create continue box
            engine::graphics::box_builder builder3(m_texture_manager.get_size("continue"));
            builder3.as_left_top(m_header_box->left_bottom()).center_vertical(m_header_box->max.y, display_box.max.y)
                .center_horizontal(display_box.min.x, display_box.max.x);
            m_continue_box.reset(new engine::math::box2_t(builder3.build()));
        }

        void win_game_over::after() {
            engine::eventbus::eventbus::get_instance().unsubscribe(this);

            m_texture_manager.unload("w_title");
            m_texture_manager.unload("continue");
        }

        void win_game_over::draw(unsigned int time_elapsed, engine::math::box2_t display_box) {
            m_color_manager.draw({0, 0, 0}, *m_header_box);
            m_texture_manager.draw("w_title", {0, 0}, *m_title_box);
            m_texture_manager.draw("continue", {0, 0}, *m_continue_box);
        }

        void win_game_over::set_controller(gui::controllers::main_map_controller &controller) {
            m_controller = &controller;
        }

        void win_game_over::on_event(engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT> &event) {
            this->m_controller->next_lvl();
        }
    }
}
