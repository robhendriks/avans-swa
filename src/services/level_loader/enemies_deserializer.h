//
// Created by Rob Hendriks on 08/12/2016.
//

#ifndef CITY_DEFENCE_ENEMIES_DESERIALIZER_H
#define CITY_DEFENCE_ENEMIES_DESERIALIZER_H

#include "../../utils/json_utils.hpp"
#include "../../domain/nations/enemy.h"
#include "enemy_deserializer.h"

using namespace domain::nations;
using namespace utils::json_utils;

namespace services {
    namespace level_loader {

        using enemy_ptr_vector = std::vector<enemy_ptr>;

        class enemies_deserializer : public json_deserializer<enemy_ptr_vector> {
        public:
            enemy_ptr_vector deserialize(const nlohmann::json &json) const override;
        };

    }
}

#endif //CITY_DEFENCE_ENEMIES_DESERIALIZER_H
