//
// Created by Rob Hendriks on 12/10/2016.
//

#ifndef CITY_DEFENCE_TEXTURE_H
#define CITY_DEFENCE_TEXTURE_H

#include "SDL.h"
#include "SDL_image.h"

namespace game {
    namespace graphics {
        class texture {
        public:
            texture(const char *filename);

            bool load(SDL_Renderer *renderer);

            void destroy();

            SDL_Texture *get_texture();

            int get_width();

            int get_height();

        private:
            const char *m_filename;
            SDL_Texture *m_texture;
            int m_width;
            int m_height;
        };
    }
}

#endif //CITY_DEFENCE_TEXTURE_H
