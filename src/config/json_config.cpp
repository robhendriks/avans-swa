//
// Created by Rob Hendriks on 19/10/2016.
//

#include "json_config.h"
#include "../utils/string_utils.h"

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

    std::string json_config::get_string(std::string key, std::string default_value) {
        json root = get(key);
        if (!root.is_null() && root.is_string()) {
            return root;
        }

        return default_value;
    }

    int json_config::get_int(std::string key, int default_value) {
        json root = get(key);
        if (!root.is_null() && root.is_number_integer()) {
            return root;
        }

        return default_value;
    }

    float json_config::get_float(std::string key, float default_value) {
        json root = get(key);
        if (!root.is_null() && root.is_number_float()) {
            return root;
        }

        return default_value;
    }

    bool json_config::get_bool(std::string key, bool default_value) {
        json root = get(key);
        if (!root.is_null() && root.is_boolean()) {
            return root;
        }

        return default_value;
    }

    long json_config::get_long(std::string key, long default_value) {
        std::string string_value = get_string(key);
        if (string_value != "") {
            try {
                return std::stol(string_value);
            } catch (...) {
                return default_value;
            }
        }

        return default_value;
    }

    json json_config::get(std::string key) {
        std::vector<std::string> keys = utils::string_utils::tokenize(key, ".");

        json root = mJSON;
        for (std::string const &k : keys) {
            if (root.is_object() && root.find(k) != root.end()) {
                root = root[k];
            } else {
                json not_found = {nullptr};
                return not_found;
            }
        }

        return root;
    }
}
