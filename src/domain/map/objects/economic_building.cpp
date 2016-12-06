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

            economic_building::economic_building(engine::math::box2_t box, const std::string &id, int hitpoints,
                                                 double health_ragen, const std::string &name,
                                                 const std::vector<std::shared_ptr<resources::resource>> &required_resources,
                                                 std::shared_ptr<domain::resources::resource> resource) : building(
                box, id, hitpoints, health_ragen, name, required_resources ) {
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

            std::shared_ptr<domain::resources::resource> economic_building::get_produced_resources() {
                return produced_resources;
            }

            void economic_building::set_produced_resource(std::shared_ptr<domain::resources::resource> resource) {
                produced_resources = resource;
            }

            void economic_building::update(domain::game_level::game_level game_level) {
                int counter = 0;
                auto resourcelist = game_level.get_resources();
                for (auto resource:resourcelist) {
                    if (resource->get_resource_type() == produced_resources->get_resource_type()) {

                        //Update gamelevel
                        resourcelist[counter]->set_count(
                            resourcelist[counter]->get_count() + produced_resources->get_count());
                        game_level.set_resources(resourcelist);
                        break;
                    }
                    counter++;
                }
            }


        }
    }
}

#endif //CITY_DEFENCE_BUILDING_CPP
