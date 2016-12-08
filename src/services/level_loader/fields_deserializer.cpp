//
// Created by Rob Hendriks on 08/12/2016.
//

#include "fields_deserializer.h"

namespace services {
    namespace level_loader {

        field_ptr_vector fields_deserializer::deserialize(const nlohmann::json &json) const {
            field_ptr_vector result;
            if (!json.is_array())
                return result;

            result.reserve(json.size());
            SDL_Log("Loading %lu field(s)...\n", json.size());

            for (auto &elem : json)
                result.push_back(json_deserialize<field_ptr>(elem));

            return result;
        }

    }
}
