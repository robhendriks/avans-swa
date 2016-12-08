#ifndef CITY_DEFENCE_BASE_FIELD_H
#define CITY_DEFENCE_BASE_FIELD_H

#include "../../engine/graphics/texture_manager.h"
#include "../../engine/observer/observee.h"
#include "map.h"
#include "objects/field_object.h"
#include "../drawable/drawable_game_object.h"
#include "../../engine/draganddrop/dropable.h"

namespace domain {
    namespace map {
        namespace objects {
            class field_object;
        }
    }
}

namespace domain {
    namespace map {
        class map;
    }
}

namespace domain {
    namespace map {
        class field : public drawable::drawable_game_object, public engine::draganddrop::dropable,
                      public engine::observer::observee<field>, public std::enable_shared_from_this<field> {
        public:

            field(map &map1, engine::math::vec2_t pos);

            ~field();

            void draw(drawable::draw_managers_wrapper &draw_managers, unsigned int time_elapsed);

            engine::math::box2_t get_box() const;

            bool drop(engine::draganddrop::dragable* dragable1);

            void set_box(std::shared_ptr<engine::math::box2_t> box) ;

            bool place_object(objects::field_object* object);

            bool has_object() const;

            objects::field_object *get_object() const;

            std::vector<std::shared_ptr<field>> get_neighbors() const;

            engine::math::vec2_t get_position() const;

            long get_weight() const;

            void set_weight(long weight);

        private:
            map &m_map;
            engine::math::vec2_t m_pos;
            objects::field_object *m_object;
            std::shared_ptr<engine::math::box2_t> m_box;
            long m_weight = 0;
        };
    }
}
#endif //CITY_DEFENCE_BASE_FIELD_H
