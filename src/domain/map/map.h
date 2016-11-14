#ifndef CITY_DEFENCE_MAP_H
#define CITY_DEFENCE_MAP_H

#include "base_map.h"
#include "base_field.h"
#include "passable_field.h"
#include <vector>

namespace domain {
    namespace map {
        class map : public base_map, public engine::observer::observer<base_field>{
        public:
            map(int tile_width, int tile_height);
            ~map();
            virtual void draw(engine::graphics::texture_manager &texture_manager, engine::math::box2_t &dest);
            virtual void unload(engine::graphics::texture_manager &texture_manager);
            std::vector<base_field *> get_fields(bool object_filter = false);
            virtual void notify(base_field *p_observee);
            void add_field(base_field* field);
            void add_fields(std::vector<base_field *> fields);
            int get_tile_width();
            int get_tile_height();
        private:
            std::vector<domain::map::base_field*> m_fields;
            std::vector<domain::map::base_field*> _fields_with_object;
            int _tile_width;
            int _tile_height;
        };
    }
}

#endif //CITY_DEFENCE_MAP_H
