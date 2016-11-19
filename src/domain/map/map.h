#ifndef CITY_DEFENCE_MAP_H
#define CITY_DEFENCE_MAP_H

#include "base_map.h"
#include "base_field.h"
#include "passable_field.h"
#include <vector>
#include <memory>

namespace domain {
    namespace map {
        class map : public base_map, public engine::observer::observer<base_field>{
        public:
            map(int tile_width, int tile_height);
            ~map();
            virtual void draw(engine::graphics::texture_manager &texture_manager, engine::math::box2_t &dest);
            virtual void unload(engine::graphics::texture_manager &texture_manager);
            std::vector<std::shared_ptr<base_field>> get_fields(bool object_filter = false);
            virtual void notify(base_field *p_observee, std::string title);
            void add_field(base_field* field);
            void add_fields(std::vector<base_field *> fields);
            int get_tile_width();
            int get_tile_height();
            int get_height();
            int get_width();
        private:
            std::vector<std::shared_ptr<domain::map::base_field>> m_fields;
            std::vector<std::shared_ptr<domain::map::base_field>> m_fields_with_object;
            int m_tile_width;
            int m_tile_height;
        };
    }
}

#endif //CITY_DEFENCE_MAP_H
