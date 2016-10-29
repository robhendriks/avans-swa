//
// Created by te on 28-Oct-16.
//

#include <SDL_image.h>
#include "texture_manager.h"

namespace engine {
    namespace texture{

        texture_manager::texture_manager(SDL_Renderer &r) : _renderer(r) {
        }

        bool texture_manager::load_texture(std::string file_name, std::string id)
        {
            SDL_Surface* temp_surface = IMG_Load(file_name.c_str());

            if (temp_surface == nullptr) {
                return false;
            }

            SDL_Texture* texture = SDL_CreateTextureFromSurface(&_renderer, temp_surface);

            SDL_FreeSurface(temp_surface);

            if (texture) {
                _texture_map[id] = texture;
                return true;
            }

            return false;
        }

        void texture_manager::draw(std::string id, int sourceX, int sourceY, int width, int height, int destX, int destY) {

            SDL_Rect src_rect, dest_rect;
            src_rect.x = sourceX;
            src_rect.y = sourceY;
            src_rect.w  = dest_rect.w = width;
            src_rect.h  = dest_rect.h = height;
            dest_rect.x = destX;
            dest_rect.y = destY;

            SDL_RenderCopy(&_renderer, _texture_map[id], &src_rect, &dest_rect);
        }
    }
}
