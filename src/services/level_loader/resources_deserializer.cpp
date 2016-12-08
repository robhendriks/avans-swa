//
// Created by Rob Hendriks on 08/12/2016.
//

#include "resources_deserializer.h"

namespace services {
    namespace level_loader {

        resource_ptr_vector resources_deserializer::deserialize(const nlohmann::json &json) const {
            resource_ptr_vector result;

            if (!json.is_object())
                return result;

            auto it = json.begin();
            for (; it != json.end(); ++it) {
                std::string key = it.key();
                int value = json.value(key, -1);

                result.push_back(std::make_shared<resource>(key, value));
            }

            return result;
        }

    }
}
