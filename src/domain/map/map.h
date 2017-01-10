#ifndef CITY_DEFENCE_MAP_H
#define CITY_DEFENCE_MAP_H

#include "field.h"
#include "../../engine/eventbus/eventbus.h"
#include "../../engine/events/display_changed.h"
#include "../drawable/abstract_drawable_game_object.h"
#include "../drawable/abstract_drawable_game_object.h"
#include <vector>
#include <memory>


namespace domain {
    namespace game_level {
        class game_level;
    }
    namespace map {
        class field;
    }
}

namespace domain {
    namespace map {
        struct field_with_range {
        public:
            field_with_range(domain::map::field &field, int range);

            domain::map::field &field;
            int range_from_origin;
        };

        class map : public drawable::abstract_drawable_game_object,
                    public engine::observer::observee<map>,
                    public engine::observer::observer<field> {
        public:
            map(engine::math::vec2_t size, engine::math::vec2_t tile_size);

            void notify(field *p_observee, std::string title);

            field *get_field(unsigned int index) const;

            field *get_field(engine::math::vec2_t position) const;

            std::vector<field*> get_fields_with_objects() const;

            std::vector<field*> get_empty_fields() const;

            std::vector<field*> get_fields() const;

            void add_field(field &field1);

            std::vector<field*> get_neighbors(engine::math::vec2_t position) const;

            unsigned int number_of_fields() const;

            engine::math::vec2_t get_tile_size() const;

            engine::math::vec2_t get_size() const;

            void draw(drawable::draw_managers_wrapper &draw_managers, unsigned int time_elapsed);

            void set_display_box(engine::math::box2_t display_box);

            void unload(drawable::draw_managers_wrapper &draw_managers);

            void update_objects(domain::game_level::game_level *game_level);

            // get all fields in a certain range from the origin
            // range = fields. 1 = one neighbour away
            std::vector<field_with_range> get_fields_in_range(int range, field *origin);

            domain::game_level::game_level *get_game_level();

            void set_game_level(domain::game_level::game_level &game_level);

        private:
            engine::math::vec2_t index_to_position(unsigned int index) const;

            unsigned int position_to_index(engine::math::vec2_t pos) const;

            engine::math::vec2_t m_size;
            engine::math::vec2_t m_tile_size;
            std::vector<domain::map::field*> m_fields;
            std::unique_ptr<engine::math::box2_t> m_dest;
            domain::game_level::game_level *m_game_level;
        };
    }
}

#endif //CITY_DEFENCE_MAP_H
