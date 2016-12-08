//
// Created by Rob Hendriks on 08/12/2016.
//

#ifndef CITY_DEFENCE_BUILDING_DESERIALIZER_H
#define CITY_DEFENCE_BUILDING_DESERIALIZER_H

#include "resources_deserializer.h"
#include "../../utils/json_utils.hpp"
#include "../../engine/math/box2.hpp"
#include "../../domain/map/objects/building.h"
#include "../../domain/map/objects/economic_building.h"
#include "../../domain/map/objects/defensive_building.h"
#include "../../domain/resources/resource.h"

using namespace domain::map::objects;
using namespace utils::json_utils;
using namespace engine::math;

namespace services {
    namespace level_loader {

        using building_ptr = std::shared_ptr<building>;

        struct building_cfg {
            int type;
            std::string id;
            std::string name;
            double hp;
            double hp_regen;
            resource_ptr_vector cost;
            resource_ptr_vector output;
        };

        using building_cfg_ptr = std::unique_ptr<building_cfg>;

        class building_deserializer : public json_deserializer<building_ptr> {
        public:
            building_ptr deserialize(const nlohmann::json &json) const override;

        private:
            building_ptr create_economic(const nlohmann::json &json, building_cfg_ptr cfg) const;

            building_ptr create_defensive(const nlohmann::json &json, building_cfg_ptr cfg) const;
        };

    }
}

#endif //CITY_DEFENCE_BUILDING_DESERIALIZER_H
