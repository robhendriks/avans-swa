//
// Created by Rob Hendriks on 19/10/2016.
//

#ifndef CITY_DEFENCE_JSON_CONFIG_H
#define CITY_DEFENCE_JSON_CONFIG_H

#include <string>
#include <fstream>
#include <exception>
#include <json.hpp>
#include "config.h"

using json = nlohmann::json;

namespace config {
    class json_config : public ::config::config {
    public:
        json_config(const char *fileName);

        ~json_config();

        void load();

        std::string get_string(std::string key, std::string default_value = "");

        int get_int(std::string key, int default_value = -1);

        float get_float(std::string key, float default_value = -1);

        long get_long(std::string key, long default_value = -1);

        json get(std::string key);
    private:
        const char *mFileName;
        json mJSON;
    };
}

#endif //CITY_DEFENCE_JSON_CONFIG_H
