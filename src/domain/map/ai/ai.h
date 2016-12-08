//
// Created by Bert on 7-12-2016.
//

#ifndef CITY_DEFENCE_AI_H
#define CITY_DEFENCE_AI_H

#include "../field.h"
#include "states/state.h"


namespace domain {
    namespace nations{
        class enemy;
    }

    namespace map {
        namespace ai{
            class ai {
            public:
                ai();
                void update(unsigned int elapsed_time);

                void set_map(std::shared_ptr<map> map);
                std::shared_ptr<map> get_map();
                void set_unit(std::shared_ptr<domain::nations::enemy> unit);
                std::shared_ptr<domain::nations::enemy> get_unit();
                void set_target_func(std::function<bool(domain::map::objects::field_object *)> target);
                std::function<bool(domain::map::objects::field_object*)> get_is_target_func();
                bool is_initialised() const;
                void set_state(std::shared_ptr<states::state> state);
                std::shared_ptr<field> get_current_field();
                void set_current_field(std::shared_ptr<field> field);
                ai clone();
            private:
                std::shared_ptr<field> m_current_field;
                std::shared_ptr<domain::map::map> m_map;
                std::shared_ptr<domain::nations::enemy> m_unit;

                // this makes the ai a implentation that only works on field objects
                // in case it needs to work for enemies this needs to be moved to a sub class and this becomes a super and then a extra
                // implementation for get_target basically
                std::function<bool(domain::map::objects::field_object*)> m_is_target;

                std::shared_ptr<states::state> m_state;

                std::shared_ptr<field> get_spawn_point();
            };
    }
}
}

#endif //CITY_DEFENCE_AI_H
