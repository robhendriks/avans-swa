//
// Created by Mark on 5-12-2016.
//

#include "economic_building.h"

#ifndef CITY_DEFENCE_BUILDING_CPP
#define CITY_DEFENCE_BUILDING_CPP

#include "building.h"
#include "road.h"

namespace domain {
    namespace map {
        namespace objects {

            economic_building::economic_building(engine::math::box2_t box,
                                                 std::shared_ptr<domain::resources::resource> resource) : building(
                    box) {
                produced_resources = resource;
            }

            economic_building::economic_building(std::shared_ptr<field> field1,
                                                 std::shared_ptr<domain::resources::resource> resource) : building(
                    field1) {
                produced_resources = resource;
            }

            economic_building::economic_building(const building &obj,
                                                 std::shared_ptr<domain::resources::resource> resource) : building(
                    obj) {
                produced_resources = resource;
            }

            std::shared_ptr<domain::resources::resource> economic_building::get_produced_resources(){
                return produced_resources;
            }

            void economic_building::set_produced_resource(std::shared_ptr<domain::resources::resource> resource)  {
                produced_resources = resource;
            }

            void economic_building::update(domain::game_level::game_level game_level){
                //TODO
            }



        }
    }
}

#endif //CITY_DEFENCE_BUILDING_CPP
