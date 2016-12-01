//
// Created by te on 10-Nov-16.
//

#include "drawable_game_object.h"
namespace domain {
    namespace drawable {
        drawable_game_object::drawable_game_object() : m_image_start_position(nullptr) {}

        /**
         * Copy constructor
         *
         * @param obj
         */
        drawable_game_object::drawable_game_object(const drawable_game_object &obj) {
            m_file_loc = obj.m_file_loc;
            m_texture = obj.m_texture;

            if (obj.m_image_start_position == nullptr) {
                m_image_start_position = nullptr;
            } else {
                m_image_start_position = std::unique_ptr<engine::math::vec2_t>(new engine::math::vec2_t(*obj.m_image_start_position));
            }
        }

        void drawable_game_object::set_draw_settings(std::string file_loc,
                                                   engine::math::vec2_t image_start_position) {
            m_file_loc = file_loc;
            m_image_start_position.reset(new engine::math::vec2_t(image_start_position));
            m_texture = nullptr;
        }

        void drawable_game_object::draw(engine::graphics::texture_manager &texture_manager, unsigned int time_elapsed) {
            load_texture_if_not_loaded_yet(texture_manager);
            draw_object(texture_manager);
        }

        void drawable_game_object::load_texture_if_not_loaded_yet(engine::graphics::texture_manager &texture_manager) {
            // in case texture hasn't been loaded in for this object.
            if (m_texture == nullptr) {
                // look if another object has loaded this specific texture in the texture manager.
                m_texture = texture_manager.find(m_file_loc);
                if (m_texture == nullptr) {
                    // in case it didn't then we need to load it in ourselves.
                    SDL_Texture* result = texture_manager.load(m_file_loc, m_file_loc);

                    // in case the texture is valid then find it again.
                    if (result != nullptr)
                        m_texture = result;
                    else // in case its not loaded in then throw a exception that loading the texture in is impossible.
                        throw std::exception();
                }
            }
        }

        void drawable_game_object::draw_object(engine::graphics::texture_manager &texture_manager) {
            texture_manager.draw(m_file_loc, *m_image_start_position, get_box());
        }

        void drawable_game_object::unload(engine::graphics::texture_manager &texture_manager) {
            texture_manager.unload(m_file_loc);
            this->m_texture = nullptr;
        }
    }
}
