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

                std::vector<std::shared_ptr<domain::resources::resource>> get_required_resources();
                void set_required_resource(std::vector<std::shared_ptr<domain::resources::resource>> resources);

                std::shared_ptr<domain::resources::resource> get_produced_resources();
                void set_produced_resource(std::shared_ptr<domain::resources::resource> resource);

            private:
                //List of required resources to constuct this building
                std::vector<std::shared_ptr<domain::resources::resource>> required_resources;

                //Resource this building produces
                std::shared_ptr<domain::resources::resource> produced_resource;
            };
        }
    }
}

#endif //CITY_DEFENCE_BUILDING_H
