#ifndef CITY_DEFENCE_BUILDING_H
#define CITY_DEFENCE_BUILDING_H

#include <string>
#include "../../../engine/draganddrop/dragable.h"
#include "dragable_field_object.h"
#include "../field.h"
#include "../../resources/resource.h"
#include "../../game_level/game_level.h"

namespace domain {
    namespace map {
        namespace objects {
            class building : public dragable_field_object {
            public:
                building(const engine::math::box2_t &box, const std::string &id, int hitpoints, double health_ragen,
                         const std::string &name,
                         const std::vector<std::shared_ptr<resources::resource>> &required_resources);

                building(engine::math::box2_t box);

                building(std::shared_ptr<field> field1);

                building(const building &obj);

                dragable_field_object *clone() const;

                bool can_place_on(field &field1) const;


                std::vector<std::shared_ptr<domain::resources::resource>> get_required_resources();
                void set_required_resource(std::vector<std::shared_ptr<domain::resources::resource>> resources);

                virtual void update(domain::game_level::game_level game_level);

                double get_health_regen();
            private:
                std::string  id;
                int hitpoints;
                double health_ragen;
                std::string name;
                int type;
                std::vector<std::shared_ptr<domain::resources::resource>> required_resources;
                void update_game_stats(domain::game_level::game_stats &game_stats1);

            };
        }
    }
}

#endif //CITY_DEFENCE_BUILDING_H
