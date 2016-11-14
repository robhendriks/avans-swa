#ifndef CITY_DEFENCE_MAP_H
#define CITY_DEFENCE_MAP_H

#include "base_map.h"
#include "base_field.h"
#include "passable_field.h"
#include <vector>

namespace domain {
    namespace map {
        class map : public base_map {
        public:
            map(int width, int height);
            ~map();
            virtual void draw(engine::graphics::texture_manager &texture_manager, engine::math::box2_t &dest);
            virtual void unload(engine::graphics::texture_manager &texture_manager);
            std::vector<std::vector<domain::map::base_field*>> &get_fields();
        private:
            std::vector<std::vector<domain::map::base_field*>> *m_fields;
        };
    }
}

#endif //CITY_DEFENCE_MAP_H
