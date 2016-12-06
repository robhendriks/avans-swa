//
// Created by Mark on 5-12-2016.
//

#ifndef CITY_DEFENCE_ECONOMIC_BUILDING_H
#define CITY_DEFENCE_ECONOMIC_BUILDING_H

#include "building.h"

namespace domain {
    namespace map {
        namespace objects {
            class economic_building : public building {
            public:
                economic_building(engine::math::box2_t box, const std::string &id, int hitpoints,
                                  double health_ragen, const std::string &name,
                                  const std::vector<std::shared_ptr<resources::resource>> &required_resources,
                                  std::shared_ptr<domain::resources::resource> resource);

                economic_building(std::shared_ptr<field> field1, std::shared_ptr<domain::resources::resource> resource);

                economic_building(const building &obj, std::shared_ptr<domain::resources::resource> resource);


                std::shared_ptr<domain::resources::resource> get_produced_resources();


                void set_produced_resource(std::shared_ptr<domain::resources::resource> resource);

                void update(domain::game_level::game_level game_level);

            private:
                std::shared_ptr<domain::resources::resource> produced_resources;

            };
        }
    }
}

#endif //CITY_DEFENCE_ECONOMIC_BUILDING_H
