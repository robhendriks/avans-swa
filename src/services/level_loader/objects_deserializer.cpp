//
// Created by Rob Hendriks on 08/12/2016.
//

#include "objects_deserializer.h"

namespace services {
    namespace level_loader {

        object_ptr_vector objects_deserializer::deserialize(const nlohmann::json &json) const {
            object_ptr_vector result;
            if (!json.is_array())
                return result;

            result.reserve(json.size());
            SDL_Log("Loading %lu object(s)...\n", json.size());

            for (auto &elem : json)
                result.push_back(json_deserialize<object_ptr>(elem));

            return result;
        }

    }
}
