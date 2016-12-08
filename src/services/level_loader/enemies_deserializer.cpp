//
// Created by Rob Hendriks on 08/12/2016.
//

#include "enemies_deserializer.h"

namespace services {
    namespace level_loader {

        enemy_ptr_vector enemies_deserializer::deserialize(const nlohmann::json &json) const {
            enemy_ptr_vector result;
            if (!json.is_array())
                return result;

            result.reserve(json.size());
            printf("Loading %lu unit(s)...\n", json.size());

            for (auto &elem : json)
                result.push_back(json_deserialize<enemy_ptr>(elem));

            return result;
        }

    }
}
