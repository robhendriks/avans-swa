//
// Created by te on 28-Oct-16.
//

#include <SDL_image.h>
#include "texture_manager.h"

namespace engine {
    namespace graphics {

        texture_manager::texture_manager(SDL_Renderer &r) : _renderer(r) {
        }

        bool texture_manager::load(std::string file_name, std::string id) {
            SDL_Surface* temp_surface = IMG_Load(file_name.c_str());

            // Check if the image is loaded
            if (temp_surface == nullptr) {
                return false;
            }

            // Create texture
            SDL_Texture* texture = SDL_CreateTextureFromSurface(&_renderer, temp_surface);

            // Get rid of the old loaded surface
            SDL_FreeSurface(temp_surface);

            // Check if the texture is created
            if (texture == nullptr) {
                return false;
            }

            // Save the texture in the map
            _texture_map[id] = texture;

            return true;
        }

        void texture_manager::unload(std::string id) {
            if (_texture_map.find(id) != _texture_map.end()) {
                SDL_DestroyTexture(_texture_map[id]);
                _texture_map.erase(id);
            }
        }

        void texture_manager::draw(std::string id, math::vec2_t image_start_position, math::box2_t dest) {

            if (_texture_map.find(id) != _texture_map.end()) {
                math::box2_t src_box(dest);
                src_box.move_to_start(image_start_position);

                SDL_Rect sdl_src = (SDL_Rect) src_box;
                SDL_Rect sdl_dest =(SDL_Rect) dest;
                SDL_RenderCopy(&_renderer, _texture_map[id], &sdl_src, &sdl_dest);
            }
        }
    }
}
