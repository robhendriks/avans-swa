//
// Created by Rob Hendriks on 08/12/2016.
//

#ifndef CITY_DEFENCE_MAP_DESERIALIZER_H
#define CITY_DEFENCE_MAP_DESERIALIZER_H

#include "../../utils/json_utils.hpp"
#include "../../domain/map/map.h"
#include "../../engine/math/vec2.hpp"
#include "fields_deserializer.h"
#include "objects_deserializer.h"
#include "json_level_loader.h"

using namespace domain::map;
using namespace utils::json_utils;
using namespace engine::math;

namespace services {
    namespace level_loader {

        using map_ptr = std::shared_ptr<map>;

        class map_deserializer : public json_deserializer<map_ptr> {
        public:
            map_ptr deserialize(const nlohmann::json &json) const override;
        };

    }
}

#endif //CITY_DEFENCE_MAP_DESERIALIZER_H
