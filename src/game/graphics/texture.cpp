//
// Created by Rob Hendriks on 12/10/2016.
//

#include "texture.h"

namespace game {
    namespace graphics {

        texture::texture(const char *filename) {
            m_filename = filename;
        }

        bool texture::load(SDL_Renderer *renderer) {
            SDL_Surface *surface = IMG_Load(m_filename);
            if (surface == NULL) {
                return false;
            }

            m_texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_QueryTexture(m_texture, NULL, NULL, &m_width, &m_height);

            SDL_FreeSurface(surface);

            return m_texture != NULL;
        }

        void texture::destroy() {
            SDL_DestroyTexture(m_texture);
        }

        SDL_Texture *texture::get_texture() {
            return m_texture;
        }

        int texture::get_width() {
            return m_width;
        }

        int texture::get_height() {
            return m_height;
        }

    }
}
