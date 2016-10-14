//
// Created by Rob Hendriks on 14/10/2016.
//

#include "display.h"

namespace game {
    namespace graphics {
        bool display::create(const char *title, int x, int y, int width, int height) {
            m_window = SDL_CreateWindow(title, x, y, width, height, SDL_WINDOW_SHOWN);
            if (m_window == NULL) {
                return false;
            }

            m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
            if (m_renderer == NULL) {
                return false;
            }

//            SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);

            return true;
        }

        void display::clear() {
            SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
            SDL_RenderClear(m_renderer);
        }

        void display::present() {
            SDL_RenderPresent(m_renderer);
        }

        void display::destroy() {
            SDL_DestroyRenderer(m_renderer);
            SDL_DestroyWindow(m_window);
        }

        SDL_Window *display::get_window() {
            return m_window;
        }

        SDL_Renderer *display::get_renderer() {
            return m_renderer;
        }
    }
}
