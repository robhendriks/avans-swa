//
// Created by Rob Hendriks on 12/10/2016.
//

#ifndef CITY_DEFENCE_BOX2_HPP
#define CITY_DEFENCE_BOX2_HPP

#include "vec2.hpp"

namespace math {

    struct box2_t {
        vec2_t min, max;

        box2_t(const vec2_t &min, const vec2_t &max)
            : min(min), max(max) {}

        box2_t(const box2_t &b)
            : min(vec2_t(b.min)), max(vec2_t(b.max)) {}

        vec2_t size() {
            return max - min;
        }

        vec2_t center() {
            return (min + max) *= 0.5f;
        }

        bool operator==(const box2_t &b) {
            return (min == b.min) && (max == b.max);
        }

        bool operator!=(const box2_t &b) {
            return (min != b.min) || (max != b.max);
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

#endif //CITY_DEFENCE_BOX2_HPP
