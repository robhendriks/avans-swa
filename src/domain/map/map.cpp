#ifndef CITY_DEFENCE_MAP_CPP
#define CITY_DEFENCE_MAP_CPP
#include "map.h"
#include <memory>
namespace domain {
    namespace map {
        map::map(int tile_width, int tile_height) : m_tile_width(tile_width), m_tile_height(tile_height) {}

        map::~map() {
        }

        std::vector<std::shared_ptr<base_field>> map::get_fields(bool object_filter) {
            if(!object_filter)
                return m_fields;
            else
                return m_fields_with_object;
        }

        // all tiles have same length and width
        void map::draw(engine::graphics::texture_manager &texture_manager, engine::math::box2_t &dest) {
            // The position for the next tile
            float base_y = dest.min.y;
            for (size_t i = 0; i < m_fields.size(); i++) {
                float x = dest.min.x + (m_fields[i]->get_x() * this->m_tile_width);
                float y = base_y + (this->m_tile_height * m_fields[i]->get_y());
                // Create tile box
                engine::math::box2_t tile_box({x, y}, {x + this->m_tile_width, y + this->m_tile_height});

                // Let the tile draw
                try {
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
            std::shared_ptr<base_field> p = std::shared_ptr<base_field>(field);
            this->m_fields.push_back(std::shared_ptr<base_field>(p));
            field->add_observer(this);

            if(field->get_placed_object() != nullptr)
                this->m_fields_with_object.push_back(std::shared_ptr<base_field>(p));
        }

        void map::add_fields(std::vector<base_field*> fields){
            for(base_field* f : fields)
                add_field(f);
        }

        void map::notify(base_field *p_observee, std::string title) {
            // find shared pointer
            if(title == "object-placed"){
            for(std::shared_ptr<base_field> f : m_fields)
                if(f.get() == p_observee){
                    this->m_fields_with_object.push_back(f);
                    this->notify_observers(this, title);
                    break;
                }
            }
        }

        int map::get_tile_width() {
            return this->m_tile_width;
        }

        int map::get_tile_height() {
            return this->m_tile_height;
        }

        int map::get_height() {
            int y = 0;

            for(auto field : this->m_fields)
                if(field->get_y()+ 1 > y)
                    y = field->get_y() + 1;

            return y * this->m_tile_height;
        }

        int map::get_width() {
            int x = 0;

            for(auto field : this->m_fields)
                if(field->get_x()+ 1 > x)
                    x = field->get_x()+1;

            return x * this->m_tile_width;
        }
    }
}
#endif //CITY_DEFENCE_MAP_CPP
