//
// Created by Rob Hendriks on 14/10/2016.
//

#ifndef CITY_DEFENCE_DISPLAY_H
#define CITY_DEFENCE_DISPLAY_H

#include <SDL.h>

namespace game {
    namespace graphics {

        class display {
        public:
            bool create(const char *title, int x, int y, int width, int height);

            void clear();

            void present();

            void destroy();

            SDL_Window *get_window();

            SDL_Renderer *get_renderer();

        private:
            SDL_Window *m_window;
            SDL_Renderer *m_renderer;
        };

    }
}

#endif //CITY_DEFENCE_DISPLAY_H
