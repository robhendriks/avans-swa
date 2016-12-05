#ifndef CITY_DEFENCE_BUILDING_CPP
#define CITY_DEFENCE_BUILDING_CPP

#include "building.h"
#include "road.h"

namespace domain {
    namespace map {
        namespace objects {

            building::building(engine::math::box2_t box) : dragable_field_object(box) {}

            building::building(std::shared_ptr<field> field1) : dragable_field_object(field1) {}

            building::building(const building &obj) : dragable_field_object(obj) {

            }

            /**
             * Make sure a building can only be placed next to a road object
             *
             * @param field1
             * @return
             */
            bool building::can_place_on(field &field1) const {
                for (auto &neighbor : field1.get_neighbors()) {
                    if (neighbor->has_object() && dynamic_cast<road*>(neighbor->get_object())) {
                        return true;
                    }
                }

                return false;
            }

            dragable_field_object *building::clone() const {
                return new building(*this);
            }

            building::building(const engine::math::box2_t &box, const std::string &id, int hitpoints,
                               double health_ragen, const std::string &name, int type,
                               const std::vector<std::shared_ptr<domain::resources::resource>> &costs, int output_min_damage,
                               int output_max_damage, int output_range,
                               const std::vector<std::shared_ptr<domain::resources::resource>> &output_resource) : dragable_field_object(box),
                                                                                          id(id), hitpoints(hitpoints),
                                                                                          health_ragen(health_ragen),
                                                                                          name(name), type(type),
                                                                                          costs(costs),
                                                                                          output_min_damage(
                                                                                              output_min_damage),
                                                                                          output_max_damage(
                                                                                              output_max_damage),
                                                                                          output_range(output_range),
                                                                                          output_resource(
                                                                                              output_resource) {}
        }
    }
}

#endif //CITY_DEFENCE_BUILDING_CPP
