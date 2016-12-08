//
// Created by Rob Hendriks on 08/12/2016.
//

#ifndef CITY_DEFENCE_FIELD_DESERIALIZER_H
#define CITY_DEFENCE_FIELD_DESERIALIZER_H

#include "../../utils/json_utils.hpp"
#include "../../domain/map/field.h"

using namespace domain::map;
using namespace utils::json_utils;

namespace services {
    namespace level_loader {

        using field_ptr = std::shared_ptr<field>;

        class field_deserializer : public json_deserializer<field_ptr> {
        public:
            field_ptr deserialize(const nlohmann::json &json) const override;
        };

    }
}

#endif //CITY_DEFENCE_FIELD_DESERIALIZER_H
