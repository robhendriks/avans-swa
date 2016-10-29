#ifndef CITY_DEFENCE_MAP_H
#define CITY_DEFENCE_MAP_H

#include "base_map.h"
#include "base_field.h"
#include "passable_field.h"
#include <vector>

namespace domain {
    namespace map {
        class map :
            public base_map {
        public:
            map();

            ~map();

        private:
            std::vector<base_field> _fields;
            std::vector<passable_field> _placed_building_fields;
        };
    }
}

#endif //CITY_DEFENCE_MAP_H
