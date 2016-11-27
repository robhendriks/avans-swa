//
// Created by robbie on 22-11-2016.
//

#ifndef CITY_DEFENCE_FIELD_OBJECT_H
#define CITY_DEFENCE_FIELD_OBJECT_H


#include "../../drawable/drawable_game_object.h"

namespace domain {
    namespace map {
        namespace objects {
            class field_object : public drawable::drawable_game_object {
            public:
                field_object() {};
                virtual ~field_object() = default;
            };
        }
    }
}

#endif //CITY_DEFENCE_FIELD_OBJECT_H
