//
// Created by Rob Hendriks on 11/10/2016.
//

#ifndef CITY_DEFENCE_INI_CONFIG_H
#define CITY_DEFENCE_INI_CONFIG_H

#include <memory>
#include "config.h"
#include "SimpleIni.h"

namespace config {
    class ini_config : public config {
    public:
        ini_config(const char *path) : config(path) {
            ini = std::unique_ptr<CSimpleIniA>(new CSimpleIniA());
            ini->SetUnicode();
        }

        bool load();

        bool reload();

        bool save();

        const char *get_value(const char *section, const char *key, const char *default_value = "");

        bool get_bool(const char *section, const char *key, bool default_value = false);

        double get_double(const char *section, const char *key, double default_value = 0);

        long get_long(const char *section, const char *key, long default_value = 0);


    private:
        std::unique_ptr<CSimpleIniA> ini;
    };
}

#endif //CITY_DEFENCE_INI_CONFIG_H
