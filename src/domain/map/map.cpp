#ifndef CITY_DEFENCE_MAP_CPP
#define CITY_DEFENCE_MAP_CPP
#include "map.h"

namespace domain {
    namespace map {
        map::map(int cols, int rows) {
            m_fields = new std::vector<std::vector<domain::map::base_field*>>;

            for (int r = 0; r < rows; r++) {
                std::vector<domain::map::base_field*> row_fields;

                for (int c = 0; c < cols; c++) {
                    engine::math::vec2_t* v = new engine::math::vec2_t(0,0);
                    row_fields.push_back(new passable_field("grass_1", "images/grass.png", v));
                }

                m_fields->push_back(row_fields);
            }
        }

        map::~map() {
            for (auto &row : *m_fields) {
                for (auto &col : row) {
                    delete col;
                }
            }
        }

        std::vector<std::vector<domain::map::base_field *>> &map::get_fields() {
            return *m_fields;
        }

        void map::draw(engine::graphics::texture_manager &texture_manager, engine::math::box2_t &dest) {
            /*
            for(auto &v : *m_fields)
                for(auto &f : v)
                  f->draw(texture_manager, );
            */
        }

        void map::unload(engine::graphics::texture_manager &texture_manager) {
            for(auto &v : *m_fields)
                for(auto &f : v)
                    f->unload(texture_manager);
        }
    }
}
#endif //CITY_DEFENCE_MAP_CPP
