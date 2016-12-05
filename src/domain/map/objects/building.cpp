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
            std::vector<std::shared_ptr<domain::resources::resource>> building::get_required_resources() {
                return required_resources;
            }

            void building::set_required_resource(std::vector<std::shared_ptr<domain::resources::resource>> resources){
                required_resources = resources;
            }

            void building::update(domain::game_level::game_level game_level){

            }

        }
    }
}

#endif //CITY_DEFENCE_BUILDING_CPP
