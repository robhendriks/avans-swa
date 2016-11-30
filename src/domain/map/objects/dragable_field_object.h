//
// Created by robbie on 18-11-2016.
//

#ifndef CITY_DEFENCE_OBJECT_H
#define CITY_DEFENCE_OBJECT_H

#include <memory>
#include "../../../engine/draganddrop/dragable.h"
#include "field_object.h"


namespace domain {
    namespace map {
        namespace objects {
            class dragable_field_object : public field_object, public engine::draganddrop::dragable {
            public:
                dragable_field_object(engine::math::box2_t box);

                dragable_field_object(std::shared_ptr<field> field1);

                virtual ~dragable_field_object();

                virtual engine::math::box2_t get_box() const;

                virtual void on_drop(engine::draganddrop::dropable *dropable1);

                virtual void on_drag(engine::math::vec2_t position);

                virtual void not_dropped();

                virtual bool can_place_on(field &field1) const;

            protected:
                engine::math::box2_t *m_start_box;
                engine::math::box2_t *m_draw_box;
            };
        }
    }
}

#endif //CITY_DEFENCE_OBJECT_H
