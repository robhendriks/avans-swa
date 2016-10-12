//
// Created by Rob Hendriks on 12/10/2016.
//

#ifndef CITY_DEFENCE_VEC2_HPP
#define CITY_DEFENCE_VEC2_HPP

#include <string>
#include <sstream>
#include <algorithm>

namespace math {

    struct vec2_t {
        int x, y;

        vec2_t(int x, int y)
            : x(x), y(y) {}

        vec2_t(const vec2_t &v)
            : x(v.x), y(v.y) {}

        vec2_t operator+(const vec2_t &v) {
            return vec2_t(x + v.x, y + v.y);
        }

        vec2_t operator+(int scalar) {
            return vec2_t(x + scalar, y + scalar);
        }

        vec2_t operator-(const vec2_t &v) {
            return vec2_t(x - v.x, y - v.y);
        }

        vec2_t operator-(int scalar) {
            return vec2_t(x - scalar, y - scalar);
        }

        vec2_t operator*(const vec2_t &v) {
            return vec2_t(x * v.x, y * v.y);
        }

        vec2_t operator*(int scalar) {
            return vec2_t(x * scalar, y * scalar);
        }

        vec2_t operator/(const vec2_t &v) {
            return vec2_t(x / v.x, y / v.y);
        }

        vec2_t operator/(int scalar) {
            return vec2_t(x / scalar, y / scalar);
        }

        vec2_t &operator=(const vec2_t &v) {
            x = v.x;
            y = v.y;
            return *this;
        }

        vec2_t &operator+=(const vec2_t &v) {
            x += v.x;
            y += v.y;
            return *this;
        }

        vec2_t &operator+=(int scalar) {
            x += scalar;
            y += scalar;
            return *this;
        }

        vec2_t &operator-=(const vec2_t &v) {
            x -= v.x;
            y -= v.y;
            return *this;
        }

        vec2_t &operator-=(int scalar) {
            x -= scalar;
            y -= scalar;
            return *this;
        }

        vec2_t &operator*=(const vec2_t &v) {
            x *= v.x;
            y *= v.y;
            return *this;
        }

        vec2_t &operator*=(int scalar) {
            x *= scalar;
            y *= scalar;
            return *this;
        }

        vec2_t &operator/=(const vec2_t &v) {
            x /= v.x;
            y /= v.y;
            return *this;
        }

        vec2_t &operator/=(int scalar) {
            x /= scalar;
            y /= scalar;
            return *this;
        }

        vec2_t &operator++() {
            ++x;
            ++y;
            return *this;
        }

        vec2_t &operator--() {
            --x;
            --y;
            return *this;
        }

        bool operator==(const vec2_t &v) {
            return (x == v.x) && (y == v.y);
        }

        bool operator!=(const vec2_t &v) {
            return (x != v.x) || (y != v.y);
        }

        vec2_t &min(const vec2_t &v) {
            x = std::min(x, v.x);
            y = std::min(y, v.y);
            return *this;
        }

        vec2_t &min(int scalar) {
            return min(vec2_t(scalar, scalar));
        }

        vec2_t &max(const vec2_t &v) {
            x = std::max(x, v.x);
            y = std::max(y, v.y);
            return *this;
        }

        vec2_t &max(int scalar) {
            return max(vec2_t(scalar, scalar));
        }

        vec2_t &clamp(vec2_t min, vec2_t max) {
            x = std::max(min.x, std::min(max.x, x));
            y = std::max(min.y, std::min(max.y, y));
            return *this;
        }

        vec2_t &clamp(int min, int max) {
            return clamp(
                vec2_t(min, min),
                vec2_t(max, max));
        }

        std::string to_string() {
            std::stringstream ss;
            ss << "vec2_t{";
            ss << "x=" << x;
            ss << ", y=" << y;
            ss << '}';
            return ss.str();
        }
    };
}

#endif //CITY_DEFENCE_VEC2_HPP
