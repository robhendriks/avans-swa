//
// Created by Mark on 5-12-2016.
//

#ifndef CITY_DEFENCE_DEFENSIVE_BUILDING_H
#define CITY_DEFENCE_DEFENSIVE_BUILDING_H

#include "building.h"

namespace domain {
    namespace map {
        namespace objects {

            class defensive_building : public building, public combat::attacker {
            public:
                defensive_building(const engine::math::box2_t &box,
                                   const std::string &id,
                                   int hitpoints,
                                   double health_ragen,
                                   const std::string &name,
                                   const std::vector<std::shared_ptr<resources::resource>> &required_resources,
                                   int range, int min_damage, int max_damage);

                dragable_field_object *clone() const;

                void update(domain::game_level::game_level game_level,unsigned int elapsed_time);
            };

        }
    }
}

#endif //CITY_DEFENCE_DEFENSIVE_BUILDING_H
