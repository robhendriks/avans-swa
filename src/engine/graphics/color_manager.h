//
// Created by robbie on 1-11-2016.
//

#ifndef CITY_DEFENCE_COLOR_MANAGER_H
#define CITY_DEFENCE_COLOR_MANAGER_H

#include "color4.hpp"
#include "../math/box2.hpp"

namespace engine {
    namespace graphics {
        class color_manager {
        public:
            color_manager(SDL_Renderer &r);
            void draw(color4_t color, math::box2_t dest);
        private:
            SDL_Renderer &_renderer;
        };
    }
}

#endif //CITY_DEFENCE_COLOR_MANAGER_H
