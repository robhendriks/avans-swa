//
// Created by robbie on 28-10-2016.
//

#ifndef CITY_DEFENCE_KEYCODES_H
#define CITY_DEFENCE_KEYCODES_H

#include <SDL_scancode.h>

namespace engine {
    namespace input {
        enum keycode {
            UNKNOWN,
            UP,
            RIGHT,
            DOWN,
            LEFT,
        };

        inline keycode sdl_scancode_to_keycode(SDL_Scancode scancode) {
            switch (scancode) {
                case SDL_SCANCODE_DOWN: return DOWN;
                case SDL_SCANCODE_UP: return UP;
                case SDL_SCANCODE_RIGHT: return RIGHT;
                case SDL_SCANCODE_LEFT: return LEFT;
                default: return UNKNOWN;
            }
        }
    }
}

#endif //CITY_DEFENCE_KEYCODES_H
