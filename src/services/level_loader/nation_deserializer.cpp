//
// Created by Rob Hendriks on 08/12/2016.
//

#include "nation_deserializer.h"

namespace services {
    namespace level_loader {

        nation_ptr nation_deserializer::deserialize(const nlohmann::json &json) const {
            if (!json.is_object()) return nullptr;

            std::string id, name, prefix;
            id = json.value("id", "");
            name = json.value("name", "");
            prefix = json.value("prefix", "_");

            if (id.empty() || name.empty() || prefix.empty()) {
                SDL_Log("Nation has missing or invalid data\n");
                return nullptr;
            }

            SDL_Log("Loading nation %s...\n", name.c_str());

            enemy_ptr_vector enemies;
            if (json.find("units") != json.end())
                enemies = json_deserialize<enemy_ptr_vector>(json["units"]);

            auto result = std::make_shared<nation>(id, name, prefix, enemies);

            for (auto &enemy : enemies)
                enemy->set_nation(result);

            return result;
        }

    }
}
