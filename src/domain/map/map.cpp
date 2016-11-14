#ifndef CITY_DEFENCE_MAP_CPP
#define CITY_DEFENCE_MAP_CPP
#include "map.h"
namespace domain {
    namespace map {
        map::map(int tile_width, int tile_height) : _tile_width(tile_width), _tile_height(tile_height) {
            for (int r = 0; r < 10; r++) {
                for (int c = 0; c < 10; c++) {
                    engine::math::vec2_t *v = new engine::math::vec2_t(0, 0);
                    this->add_field(new passable_field("grass_1", "images/grass.png", v, r, c));
                }
            }
        }

         map::~map() {
            for (auto &f : m_fields)
                delete f;
        }

        std::vector<base_field*> map::get_fields(bool object_filter) {
            if(!object_filter)
                return m_fields;
            else
                return _fields_with_object;
        }

        // all tiles have same length and width
        void map::draw(engine::graphics::texture_manager &texture_manager, engine::math::box2_t &dest) {
            // The position for the next tile
            float base_y = dest.min.y;

            for (size_t i = 0; i < m_fields.size(); i++) {
                float x = dest.min.x + (m_fields[i]->get_x() * this->_tile_width);
                float y = base_y + (this->_tile_height * m_fields[i]->get_y());
                // Create tile box
                engine::math::box2_t tile_box({x, y}, {x + this->_tile_width, y + this->_tile_height});

                // Let the tile draw
                try{
                    m_fields[i]->draw(texture_manager, tile_box);
                }
                catch(std::exception e){
                    e.what();
                }
                x += this->_tile_width;
            }
        }

        void map::unload(engine::graphics::texture_manager &texture_manager) {
            for(auto &f : m_fields)
                f->unload(texture_manager);
        }

        void map::add_field(base_field* field) {
            this->m_fields.push_back(field);
            field->add_observer(this);

            if(field->get_placed_object() != nullptr)
                this->_fields_with_object.push_back(field);
        }

        void map::add_fields(std::vector<base_field*> fields){
            for(base_field* f : fields)
                add_field(f);
        }

        void map::notify(base_field *p_observee) {
            if(std::find(this->_fields_with_object.begin(), this->_fields_with_object.end(), p_observee) == this->_fields_with_object.end())
                this->_fields_with_object.push_back(p_observee);
        }

        int map::get_tile_width() {
            return this->_tile_width;
        }

        int map::get_tile_height() {
            return this->_tile_height;
        }
    }
}
#endif //CITY_DEFENCE_MAP_CPP
