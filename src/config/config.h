//
// Created by robbie on 1-11-2016.
//

#ifndef CITY_DEFENCE_CONFIG_H
#define CITY_DEFENCE_CONFIG_H

#include <string>

namespace config {
    class config {
    public:
        virtual std::string get_string(std::string key, std::string default_value = "") = 0;
        virtual int get_int(std::string key, int default_value = -1) = 0;
        virtual long get_long(std::string key, long default_value = -1) = 0;
        virtual float get_float(std::string key, float default_value = -1) = 0;
    };
}

#endif //CITY_DEFENCE_CONFIG_H
