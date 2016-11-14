#ifndef CITY_DEFENCE_BASE_MAP_H
#define CITY_DEFENCE_BASE_MAP_H

#include "../drawable/abstract_drawable_game_object.h"

namespace domain {
    namespace map {
        class base_map : public domain::drawable::abstract_drawable_game_object{
        public:
            base_map();
            virtual ~base_map();
        };
    }
}
#endif //CITY_DEFENCE_BASE_MAP_H
