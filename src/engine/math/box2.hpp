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

            vec2_t center() {
                return (min + max) *= 0.5f;
            }

            float width() {
                return max.x - min.x;
            }

            float height() {
                return max.y - min.y;
            }

            void move_to_start(vec2_t start) {
                float x_diff = start.x - min.x;
                float y_diff = start.y - min.y;

                max.x += x_diff;
                max.y += y_diff;

                min = start;
            }

            void add(const vec2_t &vec) {
                min += vec;
                max += vec;
            }

            void to_top(const box2_t &box) {
                if (min.y < box.min.y) {
                    min.y = box.min.y;
                } else {
                    float y_diff = min.y - box.min.y;

                    max.y -= y_diff;
                    min.y -= y_diff;
                }
            }

            void to_bottom(const box2_t &box) {
                if (max.y > box.max.y) {
                    max.y = box.max.y;
                } else {
                    float y_diff = box.max.y - max.y;

                    max.y += y_diff;
                    min.y += y_diff;
                }
            }

            void to_left(const box2_t &box) {
                if (min.x < box.min.x) {
                    min.x = box.min.x;
                } else {
                    float x_diff = min.x - box.min.x;

                    max.x -= x_diff;
                    min.x -= x_diff;
                }
            }

            void to_right(const box2_t &box) {
                if (max.x > box.max.x) {
                    max.x = box.max.x;
                } else {
                    float x_diff = box.max.x - max.x;

                    max.x += x_diff;
                    min.x += x_diff;
                }
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
