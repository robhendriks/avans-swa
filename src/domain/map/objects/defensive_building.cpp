//
// Created by Mark on 5-12-2016.
//

#include "defensive_building.h"

#ifndef CITY_DEFENCE_BUILDING_CPP
#define CITY_DEFENCE_BUILDING_CPP

namespace domain {
    namespace map {
        namespace objects {

            defensive_building::defensive_building(engine::math::box2_t box, const std::string &id, int hitpoints,
                                                   double health_ragen, const std::string &name,
                                                   const std::vector<std::shared_ptr<resources::resource>> &required_resources,
                                                   int _range, int _min_dmg, int _max_dmg) : building(box,id,hitpoints,health_ragen,name,required_resources) {
                range = _range;
                min_dmg = _min_dmg;
                max_dmg = _max_dmg;
            }

            defensive_building::defensive_building(std::shared_ptr<field> field1, int _range, int _min_dmg,
                                                   int _max_dmg) : building(field1) {
                range = _range;
                min_dmg = _min_dmg;
                max_dmg = _max_dmg;
            }

            defensive_building::defensive_building(const defensive_building &obj)
                : building(obj) {
                range = obj.range;
                min_dmg = obj.min_dmg;
                max_dmg = obj.max_dmg;
            }

            int defensive_building::get_min_dmg() {
                return min_dmg;
            }

            int defensive_building::get_max_dmg() {
                return max_dmg;
            }

            int defensive_building::get_range() {
                return range;
            }

            void defensive_building::update(domain::game_level::game_level game_level) {
                //TODO
            }

            dragable_field_object *defensive_building::clone() const {
                return new defensive_building(*this);
            }
        }
    }
}

#endif //CITY_DEFENCE_BUILDING_CPP
