//
// Created by robbie on 18-11-2016.
//

#ifndef CITY_DEFENCE_OBJECT_H
#define CITY_DEFENCE_OBJECT_H

#include <memory>
#include "../../../engine/draganddrop/dragable.h"
#include "field_object.h"
#include "../../game_level/game_stats_modifier.h"


namespace domain {
    namespace map {
        namespace objects {
            class dragable_field_object : public field_object, public engine::draganddrop::dragable,
                                          public engine::observer::observee<dragable_field_object> {
            public:
                dragable_field_object(engine::math::box2_t box);

                dragable_field_object(std::shared_ptr<field> field1);

                dragable_field_object(const dragable_field_object &obj);

                virtual ~dragable_field_object() = default;

                virtual void set_box(engine::math::box2_t box);

                virtual engine::math::box2_t get_box() const;

                virtual void on_drag(engine::math::vec2_t position);

                virtual void on_drop(engine::draganddrop::dropable *dropable1);

                virtual void not_dropped();

                virtual bool can_place_on(field &field1) const;

                virtual dragable_field_object *clone() const = 0;

            protected:
                std::unique_ptr<engine::math::box2_t> m_start_box;
                std::unique_ptr<engine::math::box2_t> m_draw_box;
            };
        }
    }
}

#endif //CITY_DEFENCE_OBJECT_H
