//
// Created by te on 10-Nov-16.
//

#include "drawable_game_object.h"
namespace domain {
    namespace drawable {
        drawable_game_object::drawable_game_object(std::string id, std::string file_loc,
                                                   engine::math::vec2_t *image_start_position, int rotation) : m_id(id),
                                                                                                               m_file_loc(
                                                                                                                       file_loc),
                                                                                                               m_rotation(
                                                                                                                       rotation) {
            this->m_image_start_position = std::unique_ptr<engine::math::vec2_t>(image_start_position);
            this->m_texture = nullptr;
        }

        void
        drawable_game_object::draw(engine::graphics::texture_manager &texture_manager, engine::math::box2_t &dest) {
            load_texture_if_not_loaded_yet(texture_manager);
            draw_object(texture_manager, dest);
        }

        void drawable_game_object::load_texture_if_not_loaded_yet(engine::graphics::texture_manager &texture_manager) {
            // in case texture hasn't been loaded in for this object.
            if (this->m_texture == nullptr) {
                // look if another object has loaded this specific texture in the texture manager.
                this->m_texture = texture_manager.find(this->m_id);
                if (this->m_texture == nullptr) {
                    // in case it didn't then we need to load it in ourselves.
                    SDL_Texture* result = texture_manager.load(this->m_file_loc, this->m_id);

                    // in case the texture is valid then find it again.
                    if (result != nullptr)
                        this->m_texture = result;
                    else // in case its not loaded in then throw a exception that loading the texture in is impossible.
                        throw std::exception();
                }
            }
        }

        void drawable_game_object::draw_object(engine::graphics::texture_manager &texture_manager,
                                               engine::math::box2_t &dest) {
            texture_manager.draw(this->m_id, *m_image_start_position, dest);
        }

        void drawable_game_object::unload(engine::graphics::texture_manager &texture_manager) {
            texture_manager.unload(this->m_id);
            this->m_texture = nullptr;
        }

        engine::math::vec2_t drawable_game_object::get_texture_size() {
            if(this->m_texture == nullptr)
                return engine::math::vec2_t {-1, -1};

            int w;
            int h;
            SDL_QueryTexture(this->m_texture, NULL, NULL, &w, &h);
            return engine::math::vec2_t {(float)w, (float)h};
        }
    }
}