//
// Created by Bert on 7-12-2016.
//

#ifndef CITY_DEFENCE_AI_H
#define CITY_DEFENCE_AI_H

#include "field.h"


namespace domain {
    namespace map {

        class ai {
        public:

            ai();
            std::shared_ptr<field> get_next_field(std::shared_ptr<field> current_field);
            std::shared_ptr<field> get_spawn_point(std::shared_ptr<map> current_map);
            std::shared_ptr<field> move(std::shared_ptr<map> current_map, int times);

        };
    }
}

#endif //CITY_DEFENCE_AI_H
