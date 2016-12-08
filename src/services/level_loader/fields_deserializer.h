//
// Created by Rob Hendriks on 08/12/2016.
//

#ifndef CITY_DEFENCE_TILES_DESERIALIZER_H
#define CITY_DEFENCE_TILES_DESERIALIZER_H

#include "../../utils/json_utils.hpp"
#include "../../domain/map/field.h"
#include "field_deserializer.h"

using namespace domain::map;
using namespace utils::json_utils;

namespace services {
    namespace level_loader {

        using field_ptr_vector = std::vector<field_ptr>;

        class fields_deserializer : public json_deserializer<field_ptr_vector> {
        public:
            field_ptr_vector deserialize(const nlohmann::json &json) const override;
        };

    }
}

#endif //CITY_DEFENCE_TILES_DESERIALIZER_H
