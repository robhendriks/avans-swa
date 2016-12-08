//
// Created by Rob Hendriks on 08/12/2016.
//

#ifndef CITY_DEFENCE_RESOURCES_DESERIALIZER_H
#define CITY_DEFENCE_RESOURCES_DESERIALIZER_H

#include "../../utils/json_utils.hpp"
#include "../../domain/resources/resource.h"

using namespace domain::resources;
using namespace utils::json_utils;

namespace services {
    namespace level_loader {

        using resource_ptr = std::shared_ptr<resource>;
        using resource_ptr_vector = std::vector<resource_ptr>;

        class resources_deserializer : public json_deserializer<resource_ptr_vector> {
        public:
            resource_ptr_vector deserialize(const nlohmann::json &json) const override;
        };

    }
}


#endif //CITY_DEFENCE_RESOURCES_DESERIALIZER_H
