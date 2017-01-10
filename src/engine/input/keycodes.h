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
                HOME,
                PAGEUP,
                PAGEDOWN,
                F1,
                GRAVE,
                A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,
                SPACEBAR,
                BACKSPACE
            };

            inline bool is_numeric_keycode(const keycode &kc) {
                return kc >= D0 && kc <= D9;
            }

            inline bool is_alpha_keycode(const keycode &kc) {
                return kc >= A && kc <= Z;
            }

            inline bool is_alpha_numeric_keycode(const keycode &kc) {
                return is_numeric_keycode(kc) && is_alpha_keycode(kc);
            }

            inline bool is_input_keycode(const keycode &kc) {
                return is_alpha_keycode(kc) || kc == SPACEBAR;
            }

            inline char keycode_to_char(const keycode &kc) {
                switch (kc) {
                    case A:
                        return 'a';
                    case B:
                        return 'b';
                    case C:
                        return 'c';
                    case D:
                        return 'd';
                    case E:
                        return 'e';
                    case F:
                        return 'f';
                    case G:
                        return 'g';
                    case H:
                        return 'h';
                    case I:
                        return 'i';
                    case J:
                        return 'j';
                    case K:
                        return 'k';
                    case L:
                        return 'l';
                    case M:
                        return 'm';
                    case N:
                        return 'n';
                    case O:
                        return 'o';
                    case P:
                        return 'p';
                    case Q:
                        return 'q';
                    case R:
                        return 'r';
                    case S:
                        return 's';
                    case T:
                        return 't';
                    case U:
                        return 'u';
                    case V:
                        return 'v';
                    case W:
                        return 'w';
                    case X:
                        return 'x';
                    case Y:
                        return 'y';
                    case Z:
                        return 'z';
                    case D1:
                        return '1';
                    case D2:
                        return '2';
                    case D3:
                        return '3';
                    case D4:
                        return '4';
                    case D5:
                        return '5';
                    case D6:
                        return '6';
                    case D7:
                        return '7';
                    case D8:
                        return '8';
                    case D9:
                        return '9';
                    case SPACEBAR:
                        return ' ';
                    default:
                        return '\0';
                }
            }

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
                    case SDL_SCANCODE_HOME:
                    case SDL_SCANCODE_AC_HOME:
                        return HOME;
                    case SDL_SCANCODE_PAGEUP:
                        return PAGEUP;
                    case SDL_SCANCODE_PAGEDOWN:
                        return PAGEDOWN;
                    case SDL_SCANCODE_F1:
                        return F1;
                    case SDL_SCANCODE_A:
                        return A;
                    case SDL_SCANCODE_B:
                        return B;
                    case SDL_SCANCODE_C:
                        return C;
                    case SDL_SCANCODE_D:
                        return D;
                    case SDL_SCANCODE_E:
                        return E;
                    case SDL_SCANCODE_F:
                        return F;
                    case SDL_SCANCODE_G:
                        return G;
                    case SDL_SCANCODE_H:
                        return H;
                    case SDL_SCANCODE_I:
                        return I;
                    case SDL_SCANCODE_J:
                        return J;
                    case SDL_SCANCODE_K:
                        return K;
                    case SDL_SCANCODE_L:
                        return L;
                    case SDL_SCANCODE_M:
                        return M;
                    case SDL_SCANCODE_N:
                        return N;
                    case SDL_SCANCODE_O:
                        return O;
                    case SDL_SCANCODE_P:
                        return P;
                    case SDL_SCANCODE_Q:
                        return Q;
                    case SDL_SCANCODE_R:
                        return R;
                    case SDL_SCANCODE_S:
                        return S;
                    case SDL_SCANCODE_T:
                        return T;
                    case SDL_SCANCODE_U:
                        return U;
                    case SDL_SCANCODE_V:
                        return V;
                    case SDL_SCANCODE_W:
                        return W;
                    case SDL_SCANCODE_X:
                        return X;
                    case SDL_SCANCODE_Y:
                        return Y;
                    case SDL_SCANCODE_Z:
                        return Z;
                    case SDL_SCANCODE_GRAVE:
                        return GRAVE;
                    case SDL_SCANCODE_SPACE:
                        return SPACEBAR;
                    case SDL_SCANCODE_BACKSPACE:
                        return BACKSPACE;
                    default:
                        return UNKNOWN;
                }
            }
        }
    }
}

#endif //CITY_DEFENCE_KEYCODES_H
