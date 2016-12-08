//
// Created by Rob Hendriks on 08/12/2016.
//

#ifndef CITY_DEFENCE_OBJECT_DESERIALIZER_H
#define CITY_DEFENCE_OBJECT_DESERIALIZER_H

#include "../../utils/json_utils.hpp"
#include "../../engine/math/box2.hpp"
#include "../../domain/map/objects/field_object.h"
#include "../../domain/map/objects/road.h"
#include "../../domain/map/objects/building.h"

using namespace domain::map::objects;
using namespace utils::json_utils;
using namespace engine::math;

namespace services {
    namespace level_loader {

        using object_ptr = std::shared_ptr<field_object>;

        class object_deserializer : public json_deserializer<object_ptr> {
        public:
            object_ptr deserialize(const nlohmann::json &json) const override;
        };

    }
}

#endif //CITY_DEFENCE_OBJECT_DESERIALIZER_H
