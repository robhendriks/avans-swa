//
// Created by Mark on 5-12-2016.
//

#include "defensive_building.h"

#ifndef CITY_DEFENCE_BUILDING_CPP
#define CITY_DEFENCE_BUILDING_CPP

namespace domain {
    namespace map {
        namespace objects {

            defensive_building::defensive_building(const engine::math::box2_t &box,
                                                   const std::string &id,
                                                   int hitpoints,
                                                   double health_ragen,
                                                   const std::string &name,
                                                   const std::vector<std::shared_ptr<resources::resource>> &required_resources,
                                                   int range,
                                                   int min_damage,
                                                   int max_damage)
                : building(box, id, hitpoints, health_ragen, name, required_resources),
                  attacker(min_damage, max_damage, 2.0, range, 0) {}

            void defensive_building::update(domain::game_level::game_level game_level,unsigned int elapsed_time) {
                if(get_ai()){
                    get_ai()->update(elapsed_time);
                }
            }

            dragable_field_object* defensive_building::clone() const {
                return new defensive_building(*this);
            }

        }
    }
}

#endif //CITY_DEFENCE_BUILDING_CPP
