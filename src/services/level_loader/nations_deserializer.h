//
// Created by Rob Hendriks on 08/12/2016.
//

#ifndef CITY_DEFENCE_NATIONS_DESERIALIZER_H
#define CITY_DEFENCE_NATIONS_DESERIALIZER_H

#include "../../utils/json_utils.hpp"
#include "../../domain/nations/nation.h"

using namespace domain::nations;
using namespace utils::json_utils;

namespace services {
    namespace level_loader {

        using nation_ptr = std::shared_ptr<nation>;
        using nation_ptr_vector = std::vector<nation_ptr>;

        class nations_deserializer : public json_deserializer<nation_ptr_vector> {
        public:
            nation_ptr_vector deserialize(const nlohmann::json &json) const override;
        };

    }
}


#endif //CITY_DEFENCE_NATIONS_DESERIALIZER_H
