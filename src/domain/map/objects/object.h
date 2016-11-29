//
// Created by robbie on 18-11-2016.
//

#ifndef CITY_DEFENCE_OBJECT_H
#define CITY_DEFENCE_OBJECT_H


#include "../../../engine/draganddrop/dragable.h"
#include "../field.h"
#include "field_object.h"

namespace domain {
    namespace map {
        class field;
    }
}

namespace domain {
    namespace map {
        namespace objects {
            class object : public field_object, public engine::draganddrop::dragable {
            public:
                object(engine::math::box2_t box);

                object(field *field1);

                virtual ~object();

                void set_field(field *field1);

                virtual engine::math::box2_t get_box() const;

                virtual void on_drag(engine::math::vec2_t position);

                virtual void not_dropped();

                virtual bool can_place_on(field &field1) const;

            protected:
                engine::math::box2_t *m_start_box;
                engine::math::box2_t *m_draw_box;
                field *m_field;
            };
        }
    }
}

#endif //CITY_DEFENCE_OBJECT_H
