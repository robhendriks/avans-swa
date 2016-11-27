#ifndef CITY_DEFENCE_MAP_H
#define CITY_DEFENCE_MAP_H

#include "field.h"
#include "../../engine/events/display_changed.h"
#include "../drawable/abstract_drawable_game_object.h"
#include <vector>
#include <memory>

namespace domain {
    namespace map {
        class field;
    }
}

namespace domain {
    namespace map {
        class map : public drawable::abstract_drawable_game_object, public engine::observer::observee<map>,
                    public engine::observer::observer<field>, engine::eventbus::subscriber<engine::events::display_changed> {
        public:
            map(engine::math::vec2_t size, engine::math::vec2_t tile_size);

            ~map();

            void notify(field *p_observee, std::string title);

            std::shared_ptr<field> get_field(unsigned int index) const;

            std::shared_ptr<field> get_field(engine::math::vec2_t position) const;

            std::vector<std::shared_ptr<field>> get_fields_with_objects() const;

            std::vector<std::shared_ptr<field>> get_empty_fields() const;

            void add_field(std::shared_ptr<field> field1);

            std::vector<std::shared_ptr<field>> get_neighbors(engine::math::vec2_t position) const;

            unsigned int number_of_fields() const;

            engine::math::vec2_t get_tile_size() const;

            engine::math::vec2_t get_size() const;

            void draw(engine::graphics::texture_manager &texture_manager, unsigned int time_elapsed);

            void unload(engine::graphics::texture_manager &texture_manager);

            void on_event(engine::events::display_changed &event);

        private:
            engine::math::vec2_t index_to_position(unsigned int index) const;

            unsigned int position_to_index(engine::math::vec2_t pos) const;

            engine::math::vec2_t m_size;
            engine::math::vec2_t m_tile_size;
            std::vector<std::shared_ptr<domain::map::field>> m_fields;
            engine::math::box2_t m_dest;
        };
    }
}

#endif //CITY_DEFENCE_MAP_H
