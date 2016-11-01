//
// Created by Rob Hendriks on 12/10/2016.
//

#ifndef CITY_DEFENCE_BOX2_HPP
#define CITY_DEFENCE_BOX2_HPP

#include <SDL.h>
#include <cmath>
#include "vec2.hpp"

namespace engine {
    namespace math {

        struct box2_t {
            vec2_t min, max;

            box2_t(const vec2_t &min, const vec2_t &max)
                : min(min), max(max) {}

            box2_t(const box2_t &b)
                : min(vec2_t(b.min)), max(vec2_t(b.max)) {}

            vec2_t size() const {
                return max - min;
            }

            vec2_t center() {
                return (min + max) *= 0.5f;
            }

            void move_to_start(vec2_t start) {
                float x_diff = start.x - min.x;
                float y_diff = start.y - min.y;

                max.x += x_diff;
                max.y += y_diff;

                min = start;
            }

            void to_center(const box2_t &box) {
                if (size().x >= box.size().x || size().y >= box.size().y) {
                    max = box.max;
                    min = box.min;
                } else {
                    float x_start = (box.max.x - max.x) / 2;
                    float y_start = (box.max.y - max.y) / 2;

                    move_to_start({x_start, y_start});
                }
            }

            bool contains(const vec2_t &vec) {
                if (vec.x < min.x || vec.x > max.x ||
                    vec.y < min.y || vec.y > max.y) {
                    return false;
                }
                return true;
            }

            bool contains(const box2_t &box) {
                if ((min.x <= box.min.x) && (box.max.x <= max.x) &&
                    (min.y <= box.min.y) && (box.max.y <= max.y)) {
                    return true;
                }
                return false;
            }

            bool intersects(const box2_t &box) {
                if (box.max.x < min.x || box.min.x > max.x ||
                    box.max.y < min.y || box.min.y > max.y) {
                    return false;

                }
                return true;
            }

            bool operator==(const box2_t &b) {
                return (min == b.min) && (max == b.max);
            }

            bool operator!=(const box2_t &b) {
                return (min != b.min) || (max != b.max);
            }

            operator SDL_Rect() {
                vec2_t s = size();
                return SDL_Rect {(int) min.x, (int) min.y, (int) s.x, (int) s.y};
            }

            operator SDL_Rect*() {
                vec2_t s = size();
                return new SDL_Rect {(int) min.x, (int) min.y, (int) s.x, (int) s.y};
            }

            std::string to_string() {
                std::stringstream ss;
                ss << "{";
                ss << "min=" << min.to_string();
                ss << ", max=" << max.to_string();
                ss << '}';
                return ss.str();
            }
        };
    }
}

#endif //CITY_DEFENCE_BOX2_HPP
