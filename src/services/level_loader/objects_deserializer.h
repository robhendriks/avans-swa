//
// Created by Rob Hendriks on 08/12/2016.
//

#ifndef CITY_DEFENCE_OBJECTS_DESERIALIZER_H
#define CITY_DEFENCE_OBJECTS_DESERIALIZER_H

#include "../../utils/json_utils.hpp"
#include "object_deserializer.h"

using namespace domain::map;
using namespace utils::json_utils;

namespace services {
    namespace level_loader {

        using object_ptr_vector = std::vector<object_ptr>;

        class objects_deserializer : public json_deserializer<object_ptr_vector> {
        public:
            object_ptr_vector deserialize(const nlohmann::json &json) const override;
        };

    }
}

#endif //CITY_DEFENCE_OBJECTS_DESERIALIZER_H
