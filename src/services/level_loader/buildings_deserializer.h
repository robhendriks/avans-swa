//
// Created by Rob Hendriks on 08/12/2016.
//

#ifndef CITY_DEFENCE_BUILDINGS_DESERIALIZER_H
#define CITY_DEFENCE_BUILDINGS_DESERIALIZER_H

#include "building_deserializer.h"

namespace services {
    namespace level_loader {

        using building_ptr_vector = std::vector<building_ptr>;

        class buildings_deserializer : public json_deserializer<building_ptr_vector> {
        public:
            building_ptr_vector deserialize(const nlohmann::json &json) const override;
        };

    }
}

#endif //CITY_DEFENCE_BUILDINGS_DESERIALIZER_H
