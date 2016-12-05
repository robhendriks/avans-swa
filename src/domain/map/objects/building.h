#ifndef CITY_DEFENCE_BUILDING_H
#define CITY_DEFENCE_BUILDING_H

#include <string>
#include "../../../engine/draganddrop/dragable.h"
#include "dragable_field_object.h"
#include "../field.h"
#include "../../resources/resource.h"

namespace domain {
    namespace map {
        namespace objects {
            class building : public dragable_field_object {
            public:

                building(engine::math::box2_t box);

                building(std::shared_ptr<field> field1);

                building(const building &obj);

                dragable_field_object *clone() const;

                bool can_place_on(field &field1) const;

            private:
                std::string  id;
                int hitpoints;
                double health_ragen;
                std::string name;
                int type;
                // cost have 5 types first int = gold seccond = uranium and last = silicium!
                std::vector<std::shared_ptr<domain::resources::resource>> costs;

                int output_min_damage;
                int output_max_damage;
                int output_range;
                std::vector<std::shared_ptr<domain::resources::resource>> output_resource;
            public:
                building(const engine::math::box2_t &box, const std::string &id, int hitpoints, double health_ragen,
                         const std::string &name, int type, const std::vector<std::shared_ptr<domain::resources::resource>> &costs,
                         int output_min_damage, int output_max_damage, int output_range,
                         const std::vector<std::shared_ptr<domain::resources::resource>> &output_resource);

            };
        }
    }
}

#endif //CITY_DEFENCE_BUILDING_H
