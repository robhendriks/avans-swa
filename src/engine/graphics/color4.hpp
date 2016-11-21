//
// Created by Rob Hendriks on 19/10/2016.
//

#ifndef CITY_DEFENCE_COLOR_H
#define CITY_DEFENCE_COLOR_H

#include <string>
#include <sstream>
#include <SDL_pixels.h>

namespace engine {
    namespace graphics {
        struct color4_t {
            float a, r, g, b;

            color4_t(float r, float g, float b, float a) : a(a), r(r), g(g), b(b) {}

            color4_t(float r, float g, float b) : a(1.0f), r(g), g(g), b(b) {}

            color4_t(unsigned long hex) {
                a = ((hex >> 24) & 0x000000FF);
                r = ((hex >> 16) & 0x000000FF);
                g = ((hex >> 8) & 0x000000FF);
                b = (hex & 0x000000FF);
            }

            operator SDL_Color() {
                return SDL_Color { (Uint8)r, (Uint8)g, (Uint8)b, (Uint8)a };
            }

            std::string to_string() {
                std::stringstream ss;
                ss << "{a=" << a
                   << ", r=" << r
                   << ", g=" << g
                   << ", b=" << b
                   << '}';
                return ss.str();
            }
        };
    }
}

#endif //CITY_DEFENCE_COLOR_H
