#ifndef CITY_DEFENCE_MAP_CPP
#define CITY_DEFENCE_MAP_CPP

#include "map.h"

namespace domain {
    namespace map {
        map::map(engine::math::vec2_t size, engine::math::vec2_t tile_size) :
            m_size(size), m_tile_size(tile_size), m_fields(std::vector<std::shared_ptr<field>>(number_of_fields())),
            m_dest({{0, 0}, {size.x * m_tile_size.x, size.y * m_tile_size.y}}) {

            // Subscribe self to event
            engine::eventbus::eventbus::get_instance().subscribe((engine::eventbus::subscriber<engine::events::display_changed>*) this);
        }

        map::~map() {
            // Unsubscribe self to event
            engine::eventbus::eventbus::get_instance().unsubscribe((engine::eventbus::subscriber<engine::events::display_changed>*) this);
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
            notify_observers(this, title);
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
                    float x = m_dest.min.x + (tile_width * pos.x);
                    float y = m_dest.min.y + (tile_height * pos.y);
                    field->set_box({{x, y}, {x + tile_width, y + tile_height}});
                    field->draw(texture_manager, time_elapsed);
                }
            }
        }

        void map::unload(engine::graphics::texture_manager &texture_manager) {
            for (size_t i = 0; i < number_of_fields(); i++) {
                if (m_fields[i]) {
                    m_fields[i]->unload(texture_manager);
                }
            }
        }

        /**
         * Called whenever the display size changes, also called on the start of the view
         *
         * @param event
         */
        void map::on_event(engine::events::display_changed &event) {
            auto display_box = event.get_display_box();
            m_dest.to_left(display_box);
            m_dest.to_top(display_box);
            m_dest.to_center(display_box);
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
                return {(float)(index % ((int)m_size.x + 1)), (float)(index / ((int)m_size.x + 1))};
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
                return (unsigned  int)((pos.y * (m_size.x + 1)) + pos.x);
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
    }
}

#endif //CITY_DEFENCE_MAP_CPP
