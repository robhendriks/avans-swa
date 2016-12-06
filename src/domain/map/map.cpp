#ifndef CITY_DEFENCE_MAP_CPP
#define CITY_DEFENCE_MAP_CPP

#include <ctgmath>
#include "map.h"
#include "../../engine/graphics/box_builder.h"
#include "objects/building.h"
#include "field.h"

namespace domain {
    namespace map {
        field_with_range::field_with_range(std::shared_ptr<domain::map::field> field, int range) : field(field), range_from_origin(range) {}

        map::map(engine::math::vec2_t size, engine::math::vec2_t tile_size) :
                m_size(size), m_tile_size(tile_size), m_fields(std::vector<std::shared_ptr<field>>(number_of_fields())),
                m_dest(nullptr) {
        }

        /**
         * Get the field on the given index
         *
         * @param index
         * @return
         */
        std::shared_ptr<domain::map::field> map::get_field(unsigned int index) const {
            return m_fields[index];
        }

        std::shared_ptr<domain::map::field> map::get_field(engine::math::vec2_t position) const {
            unsigned int pos = position_to_index(position);
            if (pos < number_of_fields()) {
                return m_fields[position_to_index(position)];
            }

            return nullptr;
        }

        /**
         * Add a field to the map
         *
         * @param field1
         */
        void map::add_field(std::shared_ptr<field> field1) {
            m_fields[position_to_index(field1->get_position())] = field1;
            field1->add_observer(this);
        }

        /**
         * Get the size of a tile
         *
         * @return
         */
        engine::math::vec2_t map::get_tile_size() const {
            return m_tile_size;
        }

        /**
         * Get the map size - map of 10 by 10 == {9, 9)
         *
         * @return
         */
        engine::math::vec2_t map::get_size() const {
            return m_size;
        }


        void map::notify(field *p_observee, std::string title) {
            if (title == "object-placed") {
                if(dynamic_cast<objects::building*>(p_observee->get_object())!= nullptr)
                {
                    int range = 4;
                    // set heat for itself based on range + 1
                    p_observee->set_weight(p_observee->get_weight() + range + 1);

                    // set heat for neigbours based on range
                    auto fields = get_fields_in_range(range, p_observee);
                    for(auto& field_with_range : fields)
                    {
                        field_with_range.field->set_weight(field_with_range.field->get_weight() + field_with_range.range_from_origin);
                    }
                }
            }
            notify_observers(this, title);
        }

        std::vector<field_with_range> map::get_fields_in_range(int range, field *origin) {
            // what will be returned
            std::vector<field_with_range> result;
            // queue that still needs to be visisted
            std::vector<std::shared_ptr<field>> queue;

            // in case range is 0 or smaller return a empty list
            if(range > 0){
                // fill queue with all the neigbours from origin to make it the start point
                // for every neigbour add it to the list
                for(auto neighbour : origin->get_neighbors()){
                    queue.push_back(neighbour);
                }

                // now that we have a start point lets go.
                // lets do this as many times as the range and each time we go a layer deeeper!
                for(;range >= 0; --range){
                    // store neigbours after the queue has been finished
                    std::vector<std::shared_ptr<field>> next_queue;

                    // now go down the queue from the layer we are in now
                    for(auto& Qfield : queue){
                        // lets not forget while adding the possible field to the result we need to check if it already has been added
                        // to avoid going from id 1 to id 2 to id 1 again if they are neighbours
                        // also don't add origin.
                        bool found = false;
                        for(auto& Rfield : result){
                            if(Rfield.field == Qfield || origin == Qfield.get()){
                                found = true;
                                break;
                            }
                        }

                        // in case its not found add it and add its neighbours to the queue. (in case its found no need to add them to queue)
                        // it has already been done.
                        if(!found){
                            // add to result
                            result.push_back(field_with_range(Qfield, range));

                            // add its neighbour neighbours to the next queue
                            for(auto neigbour : Qfield->get_neighbors()){
                                next_queue.push_back(neigbour);
                            }
                        }
                    }
                    queue = next_queue;
                }
            }

            return result;
        }

        /**
         * Draw the map
         *
         * @param texture_manager
         */
        void map::draw(engine::graphics::texture_manager &texture_manager, unsigned int time_elapsed) {
            // The tile width and height
            int tile_width = (int) m_tile_size.x;
            int tile_height = (int) m_tile_size.y;

            // Calculate the tile position
            for (size_t i = 0; i < number_of_fields(); i++) {
                auto field = m_fields[i];
                if (field) {
                    auto pos = index_to_position(i);
                    float x = m_dest->min.x + (tile_width * pos.x);
                    float y = m_dest->min.y + (tile_height * pos.y);
                    field->set_box({{x,              y},
                                    {x + tile_width, y + tile_height}});
                    field->draw(texture_manager, time_elapsed);
                }
            }
        }

        /**
         * Should be atleast called once before the draw method is called
         *
         * @param display_box
         */
        void map::set_display_box(engine::math::box2_t display_box) {
            engine::graphics::box_builder builder({m_size.x * m_tile_size.x, m_size.y * m_tile_size.y});
            builder.to_center(display_box);

            m_dest.reset(new engine::math::box2_t(builder.build()));
        }

        void map::unload(engine::graphics::texture_manager &texture_manager) {
            for (size_t i = 0; i < number_of_fields(); i++) {
                if (m_fields[i]) {
                    m_fields[i]->unload(texture_manager);
                }
            }
        }

        /**
         * Get the nieghbors for the given position
         *
         * @param position
         * @return
         */
        std::vector<std::shared_ptr<field>> map::get_neighbors(engine::math::vec2_t position) const {
            std::vector<std::shared_ptr<field>> neighbors;
            // Check if the position is on the map
            if (position_to_index(position) < number_of_fields()) {
                // North neighbor
                auto north_index = position_to_index(position + engine::math::vec2_t{0, 1});
                if (north_index < number_of_fields() && m_fields[north_index]) {
                    neighbors.push_back(m_fields[north_index]);
                }
                // East neighbor
                auto east_index = position_to_index(position + engine::math::vec2_t{1, 0});
                if (east_index < number_of_fields() && m_fields[east_index]) {
                    neighbors.push_back(m_fields[east_index]);
                }
                // South neighbor
                auto south_index = position_to_index(position + engine::math::vec2_t{0, -1});
                if (south_index < number_of_fields() && m_fields[south_index]) {
                    neighbors.push_back(m_fields[south_index]);
                }
                // West neighbor
                auto west_index = position_to_index(position + engine::math::vec2_t{-1, 0});
                if (west_index < number_of_fields() && m_fields[west_index]) {
                    neighbors.push_back(m_fields[west_index]);
                }
            }

            return neighbors;
        }

        /**
         * Get the position of the index
         *
         * Note: when the index doesn't exists on the map, a vector of {-1, -1} will be returned
         *
         * @param index
         * @return engine::math::vec2_t
         */
        engine::math::vec2_t map::index_to_position(unsigned int index) const {
            if (index < number_of_fields()) {
                return {(float) (index % ((int) m_size.x + 1)), (float) (index / ((int) m_size.x + 1))};
            }

            return {-1, -1};
        }

        /**
         * Get the index of the position
         *
         * Note: when the position doesn't exists on the map, the max index + 1 (number of fields) will be returned
         *
         * @param pos
         * @return unsigned int
         */
        unsigned int map::position_to_index(engine::math::vec2_t pos) const {
            if (pos.x <= m_size.x && pos.y <= m_size.y) {
                return (unsigned int) ((pos.y * (m_size.x + 1)) + pos.x);
            }

            return number_of_fields();
        }

        /**
         * Get the number of fields on the map
         *
         * @return unsigned int
         */
        unsigned int map::number_of_fields() const {
            return (unsigned int) ((m_size.x + 1) * (m_size.y + 1));
        }

        /**
         * Get the fields where objects are placed
         *
         * @return
         */
        std::vector<std::shared_ptr<field>> map::get_fields_with_objects() const {
            std::vector<std::shared_ptr<field>> fields;
            for (auto &field1 : m_fields) {
                if (field1 && field1->has_object()) {
                    fields.push_back(field1);
                }
            }

            return fields;
        }

        /**
         * Get the fields that are empty (e.g. have no objects)
         *
         * @return
         */
        std::vector<std::shared_ptr<field>> map::get_empty_fields() const {
            std::vector<std::shared_ptr<field>> fields;
            for (auto &field1 : m_fields) {
                if (field1 && !field1->has_object()) {
                    fields.push_back(field1);
                }
            }

            return fields;
        }

        void map::update_objects(domain::game_level::game_level *game_level) {
            for (auto &field : m_fields) {
                //Check if the field has an object attached
                if (field && field->has_object()) {
                    //field has an object, now we dynamiclly cast it to a building; to filter.
                    auto building = dynamic_cast<objects::building *>(field->get_object());
                    if (building != nullptr) {
                        building->update(*game_level);
                    }
                }
            }
        }
    }
}

#endif //CITY_DEFENCE_MAP_CPP
