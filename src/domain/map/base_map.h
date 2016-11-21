#ifndef CITY_DEFENCE_BASE_MAP_H
#define CITY_DEFENCE_BASE_MAP_H

#include "../drawable/abstract_drawable_game_object.h"
#include "../../engine/observer/observer.h"
#include "base_field.h"

namespace domain {
    namespace map {
        class base_map : public domain::drawable::abstract_drawable_game_object, public engine::observer::observee<base_map>  {
        public:
            base_map();
            virtual ~base_map();
            virtual int get_tile_width() = 0;
            virtual int get_tile_height() = 0;
            virtual int get_width() = 0;
            virtual int get_height() = 0;
            virtual std::vector<std::shared_ptr<base_field>> get_fields(bool object_filter = false) = 0;
        };
    }
}
#endif //CITY_DEFENCE_BASE_MAP_H
