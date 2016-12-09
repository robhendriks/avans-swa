//
// Created by robbie on 28-10-2016.
//

#ifndef CITY_DEFENCE_KEYCODES_H
#define CITY_DEFENCE_KEYCODES_H

#include <SDL_scancode.h>

namespace engine {
    namespace input {
        namespace keycodes {
            enum keycode {
                UNKNOWN,
                UP,
                RIGHT,
                DOWN,
                LEFT,
                D0,
                D1,
                D2,
                D3,
                D4,
                D5,
                D6,
                D7,
                D8,
                D9,
                NP0,
                NP1,
                NP2,
                NP3,
                NP4,
                NP5,
                NP6,
                NP7,
                NP8,
                NP9,
                ENTER,
                PAUSE,
                ESCAPE,
            };

            inline keycode sdl_scancode_to_keycode(const SDL_Scancode &scancode) {
                switch (scancode) {
                    case SDL_SCANCODE_DOWN:
                        return DOWN;
                    case SDL_SCANCODE_UP:
                        return UP;
                    case SDL_SCANCODE_RIGHT:
                        return RIGHT;
                    case SDL_SCANCODE_LEFT:
                        return LEFT;
                    case SDL_SCANCODE_0:
                        return D0;
                    case SDL_SCANCODE_1:
                        return D1;
                    case SDL_SCANCODE_2:
                        return D2;
                    case SDL_SCANCODE_3:
                        return D3;
                    case SDL_SCANCODE_4:
                        return D4;
                    case SDL_SCANCODE_5:
                        return D5;
                    case SDL_SCANCODE_6:
                        return D6;
                    case SDL_SCANCODE_7:
                        return D7;
                    case SDL_SCANCODE_8:
                        return D8;
                    case SDL_SCANCODE_9:
                        return D9;
                    case SDL_SCANCODE_KP_0:
                        return NP0;
                    case SDL_SCANCODE_KP_1:
                        return NP1;
                    case SDL_SCANCODE_KP_2:
                        return NP2;
                    case SDL_SCANCODE_KP_3:
                        return NP3;
                    case SDL_SCANCODE_KP_4:
                        return NP4;
                    case SDL_SCANCODE_KP_5:
                        return NP5;
                    case SDL_SCANCODE_KP_6:
                        return NP6;
                    case SDL_SCANCODE_KP_7:
                        return NP7;
                    case SDL_SCANCODE_KP_8:
                        return NP8;
                    case SDL_SCANCODE_KP_9:
                        return NP9;
                    case SDL_SCANCODE_KP_ENTER:
                    case SDL_SCANCODE_RETURN:
                    case SDL_SCANCODE_RETURN2:
                        return ENTER;
                    case SDL_SCANCODE_PAUSE:
                        return PAUSE;
                    case SDL_SCANCODE_ESCAPE:
                        return ESCAPE;
                    default:
                        return UNKNOWN;
                }
            }
        }
    }
}

#endif //CITY_DEFENCE_KEYCODES_H
