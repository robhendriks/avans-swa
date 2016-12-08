//
// Created by Rob Hendriks on 08/12/2016.
//

#include "enemy_deserializer.h"

namespace services {
    namespace level_loader {

        enemy_ptr enemy_deserializer::deserialize(const nlohmann::json &json) const {
            if (!json.is_object()) return nullptr;

            std::string name, type;
            double hitpoints, movement_speed, min_damage, max_damage, oppertunity_cost, attacks_per_second, granted_xp, range;

            name = json.value("name", "");
            type = json.value("type", "");
            hitpoints = json.value("hitpoints", 100.0);
            max_damage = json.value("max-damage", 10.0);
            min_damage = json.value("min-damage", 20.0);
            movement_speed = json.value("movement-speed", 1.0);
            oppertunity_cost = json.value("oppertunity-cost", 1.0);
            attacks_per_second = json.value("attacks-per-second", 1.0);
            granted_xp = json.value("granted-xp", 1.0);
            range = json.value("range", 2.0);

            if (name.empty() || type.empty() || hitpoints <= 0 || min_damage < 0 || max_damage < 0 ||
                movement_speed <= 0 || oppertunity_cost < 0) {
                SDL_Log("Unit has missing or invalid data\n");
                return nullptr;
            }

            auto result = std::make_shared<enemy>(name,
                                           static_cast<int>(min_damage),
                                           static_cast<int>(max_damage),
                                           attacks_per_second,
                                           static_cast<int>(hitpoints),
                                           static_cast<int>(granted_xp),
                                           static_cast<int>(range),
                                           movement_speed,
                                           (type == "boss"),
                                           static_cast<int>(oppertunity_cost));

            result->set_draw_settings("images/building-a.png");
            return result;
        }

    }
}
