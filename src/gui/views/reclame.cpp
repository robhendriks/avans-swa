//
// Created by Leendert on 21-12-2016.
//

#include "reclame.h"
#include "../../engine/graphics/box_builder.h"
#include "time.h"

namespace gui {
    namespace views {

        reclame::reclame(help &help_view) : m_help_view(help_view),
                                            m_texture_manager(m_help_view.m_top_bar.m_texture_manager),
                                            m_reclame_image("images/reclame.png"), m_show(false){

        }

        void reclame::set_image(std::string image) {
            m_reclame_image = image;
        }

        void reclame::before() {

            m_help_view.before();
            // Make sure it's not shown
            m_show = false;
            // Calculate the grey_panel scale factor
            auto image_size = m_texture_manager.get_size("h_image");
            float x_scale = image_size.x / 92;
            float y_scale = image_size.y / 92;
            float scale = (x_scale > y_scale ? x_scale : y_scale);

            // Load textures
            m_texture_manager.load_from_svg("images/ui-pack.svg", {{1,   310},
                                                                   {101, 410}}, scale, "h_grey_panel");
            m_texture_manager.load_from_svg("images/ui-pack.svg", {{758, 625},
                                                                   {794, 661}}, 1, "h_red_circle");
            m_texture_manager.load_from_svg("images/ui-pack.svg", {{9,  703},
                                                                   {27, 721}}, 1, "h_white_cross");

            // Subscribe to events
            auto &eventbus = engine::eventbus::eventbus::get_instance();
            eventbus.subscribe(
                dynamic_cast<engine::eventbus::subscriber<engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT>> *>(this));
            eventbus.subscribe(dynamic_cast<engine::eventbus::subscriber<engine::events::key_down> *>(this));
        }

        void reclame::on_display_change(engine::math::box2_t display_box) {

            m_help_view.on_display_change(display_box);
            // Create the overlay box
            engine::graphics::box_builder builder1(display_box.size() - engine::math::vec2_t{0, 32});
            // builder1.as_left_top(m_top_bar.m_bar_box->left_bottom());
            m_overlay_box.reset(new engine::math::box2_t(builder1.build()));

            // Create the reclame box
            engine::graphics::box_builder builder2(m_texture_manager.get_size("h_grey_panel"));
            builder2.to_center(*m_overlay_box);
            m_reclame_box.reset(new engine::math::box2_t(builder2.build()));

            // Create the right top cross
            engine::graphics::box_builder builder3(m_texture_manager.get_size("h_red_circle"));
            builder3.as_center(m_reclame_box->right_top()).add_margin({-4, 8});
            m_cross_circle_box.reset(new engine::math::box2_t(builder3.build()));

            engine::graphics::box_builder builder4(m_texture_manager.get_size("h_white_cross"));
            builder4.to_center(*m_cross_circle_box);
            m_cross_box.reset(new engine::math::box2_t(builder4.build()));

            // Create the image box
            engine::graphics::box_builder builder5(m_texture_manager.get_size("h_image"));
            builder5.to_center(*m_reclame_box);
            m_image_box.reset(new engine::math::box2_t(builder5.build()));
        }

        void reclame::draw(unsigned int time_elapsed, engine::math::box2_t display_box) {
            m_help_view.draw(time_elapsed, display_box);

            if (m_show) {
                if (m_help_view.m_help_loaded) {

                    // Load the texture
                    srand(time(NULL));
                    int random_reclame = rand() % 11 + 1;
                    std::string random_image_result;
                    random_image_result = "images/reclame" + std::to_string(random_reclame) + ".png";
                    //set random img
                    m_reclame_image = random_image_result;
                    m_help_view.m_top_bar.m_texture_manager.load(m_reclame_image, "h_image");
                    m_help_view.m_help_loaded = false;
                }
                // Draw the overlay
                m_help_view.m_top_bar.m_color_manager.draw({0, 0, 0, 180}, *m_overlay_box);

                // reclame (wrapper)
                m_texture_manager.draw("h_grey_panel", *m_reclame_box);

                // reclame (wrapper) cross
                m_texture_manager.draw("h_red_circle", *m_cross_circle_box);
                m_texture_manager.draw("h_white_cross", *m_cross_box);

                // reclame image
                m_texture_manager.draw("h_image", *m_image_box);
            }
        }

        void reclame::on_event(engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT> &event) {
            auto *position = engine::input::input_handler::get_instance()->get_mouse_position();

            if (m_show) {
                if (m_cross_circle_box->contains(*position)) {
                    m_help_view.m_top_bar.m_menu_controller->load();
                }
            }
        }

        void reclame::on_event(engine::events::key_down &event) {
            if (m_show) {
                if (event.get_keycode() == engine::input::keycodes::keycode::ESCAPE) {
                    toggle_show();
                }
            }
        }

        void reclame::after() {
            m_help_view.after();

            // Unload the texture
            m_texture_manager.unload("h_image");

            // Unload textures
            m_texture_manager.unload("h_grey_panel");
            m_texture_manager.unload("h_red_circle");
            m_texture_manager.unload("h_white_cross");

            // Unsubscribe to events
            auto &eventbus = engine::eventbus::eventbus::get_instance();
            eventbus.unsubscribe(
                dynamic_cast<engine::eventbus::subscriber<engine::events::mouse_button_down<engine::input::mouse_buttons::LEFT>> *>(this));
            eventbus.unsubscribe(dynamic_cast<engine::eventbus::subscriber<engine::events::key_down> *>(this));
        }

        void reclame::toggle_show() {
            m_show = !m_show;

            // Call callbacks
            for (auto &callback : m_callbacks) {
                callback(m_show);
            }
        }

        void reclame::call_on_show_change(std::function<void(bool)> callback) {
            m_callbacks.push_back(callback);
        }
    }
}
