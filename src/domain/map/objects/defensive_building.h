//
// Created by Mark on 5-12-2016.
//

#ifndef CITY_DEFENCE_DEFENSIVE_BUILDING_H
#define CITY_DEFENCE_DEFENSIVE_BUILDING_H
#include "building.h"

namespace domain {
    namespace map {
        namespace objects {
            class defensive_building : public building
            {
            public:
                defensive_building(engine::math::box2_t box,  const std::string &id, int hitpoints,
                                   double health_ragen, const std::string &name,
                                   const std::vector<std::shared_ptr<resources::resource>> &required_resources, int _range, int _min_dmg, int _max_dmg);

                defensive_building(std::shared_ptr<field> field1, int _range, int _min_dmg, int _max_dmg);

                defensive_building(const defensive_building &obj);

                int get_min_dmg();
                int get_max_dmg();
                int get_range();

                void update(domain::game_level::game_level game_level);

            private:
                int min_dmg;
                int max_dmg;
                int range;


            };
        }
    }
}

#endif //CITY_DEFENCE_DEFENSIVE_BUILDING_H
