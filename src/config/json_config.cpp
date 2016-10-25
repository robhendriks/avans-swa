//
// Created by Rob Hendriks on 19/10/2016.
//

#include "json_config.h"

namespace config {
    json_config::json_config(const char *fileName) : mFileName(fileName), mJSON(json()) {}

    json_config::~json_config() {}

    void json_config::load() {
        std::ifstream ifs(mFileName);
        if (!ifs.is_open()) {
            throw std::runtime_error(std::string("Unable to open file: ") + mFileName);
        }
        ifs >> mJSON;
    }

    const char *json_config::get_file_name() {
        return mFileName;
    }

    json json_config::get_json() {
        return mJSON;
    }
}
