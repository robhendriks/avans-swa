//
// Created by Rob Hendriks on 19/10/2016.
//

#ifndef CITY_DEFENCE_JSON_CONFIG_H
#define CITY_DEFENCE_JSON_CONFIG_H

#include <string>
#include <fstream>
#include <exception>
#include <json.hpp>

using json = nlohmann::json;

namespace config {
    class json_config {
    public:
        json_config(const char *fileName);

        ~json_config();

        void load();

        const char *get_file_name();

        json get_json();

    private:
        const char *mFileName;
        json mJSON;
    };
}

#endif //CITY_DEFENCE_JSON_CONFIG_H
