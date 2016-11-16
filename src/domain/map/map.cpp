#ifndef CITY_DEFENCE_MAP_CPP
#define CITY_DEFENCE_MAP_CPP
#include "map.h"
#include <memory>
namespace domain {
    namespace map {
        map::map(int tile_width, int tile_height) : _tile_width(tile_width), _tile_height(tile_height) {}

         map::~map() {
        }

        std::vector<std::shared_ptr<base_field>> map::get_fields(bool object_filter) {
            if(!object_filter)
                return m_fields;
            else
                return _fields_with_object;
        }

        // all tiles have same length and width
        void map::draw(engine::graphics::texture_manager &texture_manager, engine::math::box2_t &dest) {
            // The position for the next tile
            float base_y = dest.min.y;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
            auto b = m_fields.at(0)->get_placed_object();
#pragma GCC diagnostic pop

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
            }
        }

        void map::unload(engine::graphics::texture_manager &texture_manager) {
            for(auto &f : m_fields)
                f->unload(texture_manager);
        }

        void map::add_field(base_field* field) {
            this->m_fields.push_back(std::shared_ptr<base_field>(field));
            field->add_observer(this);

            if(field->get_placed_object() != nullptr)
                this->_fields_with_object.push_back(std::shared_ptr<base_field>(field));
        }

        void map::add_fields(std::vector<base_field*> fields){
            for(base_field* f : fields)
                add_field(f);
        }

        void map::notify(base_field *p_observee) {
           for(std::shared_ptr<base_field> p : this->_fields_with_object){
               if(p.get() == p_observee){
                   this->_fields_with_object.push_back(std::shared_ptr<base_field>(p_observee));
                   break;
               }
           }
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
