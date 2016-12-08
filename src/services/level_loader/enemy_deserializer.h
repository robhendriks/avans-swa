//
// Created by Rob Hendriks on 08/12/2016.
//

#ifndef CITY_DEFENCE_ENEMY_DESERIALIZER_H
#define CITY_DEFENCE_ENEMY_DESERIALIZER_H

#include "../../utils/json_utils.hpp"
#include "../../domain/nations/enemy.h"

using namespace domain::nations;
using namespace utils::json_utils;

namespace services {
    namespace level_loader {

        using enemy_ptr = std::shared_ptr<enemy>;

        class enemy_deserializer : public json_deserializer<enemy_ptr> {
        public:
            enemy_ptr deserialize(const nlohmann::json &json) const override;
        };

    }
}

#endif //CITY_DEFENCE_ENEMY_DESERIALIZER_H
