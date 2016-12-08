//
// Created by Rob Hendriks on 08/12/2016.
//

#ifndef CITY_DEFENCE_NATION_DESERIALIZER_H
#define CITY_DEFENCE_NATION_DESERIALIZER_H

#include "../../utils/json_utils.hpp"
#include "../../domain/nations/nation.h"
#include "enemies_deserializer.h"

using namespace domain::nations;
using namespace utils::json_utils;

namespace services {
    namespace level_loader {

        using nation_ptr = std::shared_ptr<nation>;

        class nation_deserializer : public json_deserializer<nation_ptr> {
        public:
            nation_ptr deserialize(const nlohmann::json &json) const override;
        };

    }
}

#endif //CITY_DEFENCE_NATION_DESERIALIZER_H
