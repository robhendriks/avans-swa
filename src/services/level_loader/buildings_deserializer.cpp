//
// Created by Rob Hendriks on 08/12/2016.
//

#include "buildings_deserializer.h"

namespace services {
    namespace level_loader {

        building_ptr_vector buildings_deserializer::deserialize(const nlohmann::json &json) const {
            building_ptr_vector result;

            if (!json.is_array())
                return result;

            result.reserve(json.size());
            SDL_Log("Loading %lu building(s)...\n", json.size());

            for (auto &elem : json)
                result.push_back(json_deserialize<building_ptr>(elem));

            return result;
        }

    }
}
