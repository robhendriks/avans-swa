//
// Created by te on 14-Nov-16.
//

#ifndef CITY_DEFENCE_ROAD_H
#define CITY_DEFENCE_ROAD_H

#include <string>
#include "../../../engine/draganddrop/dragable.h"
#include "dragable_field_object.h"

namespace domain {
    namespace map {
        namespace objects {
            class road : public dragable_field_object {
            public:

                road(engine::math::box2_t box, std::string type);

                road(field &field1, std::string type);

                road(const road &obj);

                dragable_field_object *clone() const;

                void update_game_stats(domain::game_level::game_stats &game_stats1, std::string action);

                std::string get_type() const;

            private:
                std::string m_type;
            };
        }
    }
}


#endif //CITY_DEFENCE_ROAD_H
