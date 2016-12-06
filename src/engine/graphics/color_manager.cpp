//
// Created by robbie on 1-11-2016.
//

#include "color_manager.h"

namespace engine {
    namespace graphics {

        color_manager::color_manager(SDL_Renderer &renderer) : m_renderer(renderer) {
            SDL_SetRenderDrawBlendMode(&m_renderer, SDL_BLENDMODE_BLEND);
        }

        void color_manager::draw(color4_t color, math::box2_t dest) {
            SDL_Color sdl_color = (SDL_Color) color;
            SDL_SetRenderDrawColor(&m_renderer, sdl_color.r, sdl_color.g, sdl_color.b, sdl_color.a);
            SDL_Rect sdl_rect = (SDL_Rect) dest;
            SDL_RenderFillRect(&m_renderer, &sdl_rect);

//            SDL_Color sdl_color = (SDL_Color) color;
//            SDL_Rect sdl_rect = (SDL_Rect) dest;
//            SDL_FillRect(&_surface, &sdl_rect, SDL_MapRGBA(_surface.format, sdl_color.r, sdl_color.g, sdl_color.b, sdl_color.a));
        }
    }
}
