//
// Created by te on 28-Oct-16.
//

#include <SDL_image.h>
#include "texture_manager.h"
namespace game{
    namespace texture{

        texture_manager::texture_manager(SDL_Renderer* r) {
            this->_texture_map = new std::map <std::string, SDL_Texture*>();
            this->_renderer = r;
        }


        bool texture_manager::load_texture(std::string file_name, std::string id)
        {
            SDL_Surface* tempSurface = IMG_Load(file_name.c_str());

            if (tempSurface == nullptr)
            {
                return false;
            }

            SDL_Texture* texture = SDL_CreateTextureFromSurface(_renderer, tempSurface);

            SDL_FreeSurface(tempSurface);

            if (texture)
            {
                (_texture_map)->operator[](id) = texture;
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

            SDL_Texture* t = (_texture_map)->operator[](id);
            SDL_RenderCopy(_renderer, t, &src_rect, &dest_rect);
        }

        texture_manager::~texture_manager() {
            delete this->_texture_map;
        }
    }
}