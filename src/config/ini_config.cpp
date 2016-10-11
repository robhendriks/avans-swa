//
// Created by Rob Hendriks on 11/10/2016.
//

#include "ini_config.h"

namespace config {

    bool ini_config::load() {
        return (ini->LoadFile(m_path) == 0);
    }

    bool ini_config::reload() {
        return load();
    }

    bool ini_config::save() {
        return (ini->SaveFile(m_path) == 0);
    }

    const char *ini_config::get(const char *section, const char *key, const char *default_value) {
        return ini->GetValue(section, key, default_value);
    }

    bool ini_config::get(const char *section, const char *key, bool default_value) {
        return ini->GetBoolValue(section, key, default_value);
    }

    double ini_config::get(const char *section, const char *key, double default_value) {
        return ini->GetDoubleValue(section, key, default_value);
    }

    long ini_config::get(const char *section, const char *key, long default_value) {
        return ini->GetLongValue(section, key, default_value);
    }

}
