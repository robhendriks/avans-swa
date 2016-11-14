//
// Created by robbie on 1-11-2016.
//

#include "color_manager.h"

namespace engine {
    namespace graphics {

        color_manager::color_manager(SDL_Renderer &r) : _renderer(r) {
        }

        void color_manager::draw(color4_t color, math::box2_t dest) {
            SDL_Rect sdl_dest = (SDL_Rect) dest;
            SDL_RenderDrawRect(&_renderer, &sdl_dest);
        }
    }
}
