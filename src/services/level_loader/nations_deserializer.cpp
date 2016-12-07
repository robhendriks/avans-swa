//
// Created by Rob Hendriks on 08/12/2016.
//

#include "nations_deserializer.h"

namespace services {
    namespace level_loader {

        nation_ptr_vector nations_deserializer::deserialize(const nlohmann::json &json) const {
            nation_ptr_vector result;
            if (!json.is_array())
                return result;

            result.reserve(json.size());
            printf("Loading %lu nation(s)...\n", json.size());

            for (auto &elem : json)
                result.push_back(json_deserialize<nation_ptr>(elem));

            return result;
        }

    }
}
