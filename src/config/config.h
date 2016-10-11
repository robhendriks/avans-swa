//
// Created by Rob Hendriks on 11/10/2016.
//

#ifndef CITY_DEFENCE_CONFIG_H
#define CITY_DEFENCE_CONFIG_H

namespace config {
    class config {
    public:
        config(const char *path);

        virtual bool load() = 0;

        virtual bool reload() = 0;

        virtual bool save() = 0;

    protected:
        const char *m_path;
    };
}

#endif //CITY_DEFENCE_CONFIG_H
