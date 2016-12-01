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

            box2_t(float width, float height, const vec2_t &center_point)
                : min(vec2_t({center_point.x - (width / 2), center_point.y - (height / 2)})),
                  max(vec2_t({center_point.x + (width / 2), center_point.y + (height / 2)})) {}

            box2_t(const float x1, const float y1, const float x2, const float y2)
                : min{x1, y1}, max{x2, y2} {}

            vec2_t size() const {
                return max - min;
            }

            vec2_t center() const {
                return (min + max) *= 0.5f;
            }

            float width() {
                return max.x - min.x;
            }

            float height() {
                return max.y - min.y;
            }

            vec2_t right_top() {
                return vec2_t(max.x, min.y);
            }

            vec2_t right_bottom() {
                return max;
            }

            vec2_t left_top() {
                return min;
            }

            vec2_t left_bottom() {
                return vec2_t(min.x, max.y);
            }

            void add(const vec2_t &vec) {
                min += vec;
                max += vec;
            }

            bool contains(const vec2_t &vec) const {
                return !(vec.x < min.x || vec.x > max.x ||
                    vec.y < min.y || vec.y > max.y);
            }

            bool contains(const box2_t &box) const {
                return (min.x <= box.min.x) && (box.max.x <= max.x) &&
                       (min.y <= box.min.y) && (box.max.y <= max.y);
            }

            bool intersects(const box2_t &box) {
                return !(box.max.x < min.x || box.min.x > max.x ||
                    box.max.y < min.y || box.min.y > max.y);
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
