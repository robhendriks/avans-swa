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
                                  const std::vector<resources::resource*> &required_resources,
                                  domain::resources::resource &resource);

                economic_building(field &field1, const std::string &id, int hitpoints,
                                  double health_ragen, const std::string &name,
                                  const std::vector<resources::resource*> &required_resources,
                                  domain::resources::resource &resource);

                economic_building(const economic_building &obj);

                dragable_field_object *clone() const;

                domain::resources::resource &get_produced_resources();

                void update(domain::game_level::game_level &game_level);

                void draw(drawable::draw_managers_wrapper &draw_managers, unsigned int time_elapsed);

            private:
                domain::resources::resource &produced_resources;
            };
        }
    }
}

#endif //CITY_DEFENCE_ECONOMIC_BUILDING_H
