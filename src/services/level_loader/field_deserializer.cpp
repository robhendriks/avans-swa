//
// Created by Rob Hendriks on 08/12/2016.
//

#include "field_deserializer.h"

namespace services {
    namespace level_loader {

        field_ptr field_deserializer::deserialize(const nlohmann::json &json) const {
            if (!json.is_object()) return nullptr;

            // TODO

            return nullptr;
        }

    }
}
