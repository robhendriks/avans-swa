//
// Created by Rob Hendriks on 08/12/2016.
//

#include "building_deserializer.h"

namespace services {
    namespace level_loader {

        building_ptr building_deserializer::deserialize(const nlohmann::json &json) const {
            if (!json.is_object())
                return nullptr;

            auto cfg = std::make_unique<building_cfg>();

            cfg->id = json.value("id", "");
            cfg->name = json.value("name", "");
            cfg->type = json.value("type", -1);

            cfg->hp = json.value("hitpoints", -1.0);
            cfg->hp_regen = json.value("health-regen", -1.0);

            if (cfg->id.empty() || cfg->name.empty() || cfg->hp < 1.0 || cfg->hp_regen <= 0.0) {
                SDL_Log("Building has missing or invalid data\n");
                return nullptr;
            }

            // Get cost resources
            if (json.find("cost") != json.end())
                cfg->cost = json_deserialize<resource_ptr_vector>(json["cost"]);
            // Get output resources
            if (json.find("output") != json.end())
                cfg->output = json_deserialize<resource_ptr_vector>(json["output"]);

            switch (cfg->type) {
                case 1:
                    return create_economic(json, std::move(cfg));
                case 2:
                    return create_defensive(json, std::move(cfg));
                default:
                    SDL_Log("Building has invalid type\n");
                    return nullptr;
            }
        }

        building_ptr
        building_deserializer::create_economic(const nlohmann::json &json, const building_cfg_ptr &cfg) const {
            auto result = std::make_shared<economic_building>(box2_t{0, 0, 64, 64},
                                                               cfg->id,
                                                               static_cast<int>(cfg->hp),
                                                               cfg->hp_regen,
                                                               cfg->name,
                                                               cfg->cost,
                                                               cfg->output.front()); // TODO: swap .front() with the entire list

            result->set_draw_settings(std::string("images/buildings/") + cfg->id + ".png");
            return result;
        }

        building_ptr
        building_deserializer::create_defensive(const nlohmann::json &json, const building_cfg_ptr &cfg) const {
            int range = -1;
            double min_damage = -1;
            double max_damage = -1;

            if (json.find("properties") != json.end()) {
                auto properties = json["properties"];
                if (properties.is_object()) {
                    range = properties.value("range", range);
                    min_damage = properties.value("range", min_damage);
                    max_damage = properties.value("range", max_damage);
                }
            }

            auto result = std::make_shared<defensive_building>(box2_t{10, 10, 42, 42},
                                                               cfg->id,
                                                               static_cast<int>(cfg->hp),
                                                               cfg->hp_regen,
                                                               cfg->name,
                                                               cfg->cost,
                                                               range,
                                                               static_cast<int>(min_damage),
                                                               static_cast<int>(max_damage));

            result->set_draw_settings(std::string("images/buildings/") + cfg->id + ".png");
            return result;
        }

    }
}
