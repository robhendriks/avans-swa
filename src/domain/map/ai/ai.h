//
// Created by Bert on 7-12-2016.
//

#ifndef CITY_DEFENCE_AI_H
#define CITY_DEFENCE_AI_H

#include "../field.h"
#include "states/state.h"
#include "../../combat/attacker.h"
#include "../../combat/defender.h"


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
                void set_unit(std::shared_ptr<domain::combat::attacker> unit);
                std::shared_ptr<domain::combat::attacker> get_unit();
                void set_new_target_func(std::function<domain::combat::defender* (domain::map::field* origin, domain::map::ai::ai* ai)>  target);
                std::function<domain::combat::defender* (domain::map::field* origin, domain::map::ai::ai* ai)>  get_new_target_func();
                bool is_initialised() const;
                void set_state(std::shared_ptr<states::state> state);
                std::shared_ptr<states::state> get_state() const ;
                std::shared_ptr<field> get_current_field();
                void set_current_field(std::shared_ptr<field> field);
                ai clone();
            private:
                std::shared_ptr<field> m_current_field;
                std::shared_ptr<domain::map::map> m_map;
                std::shared_ptr<domain::combat::attacker> m_unit;
                std::function<domain::combat::defender* (domain::map::field* origin, domain::map::ai::ai* ai)> m_new_target_func;
                std::shared_ptr<states::state> m_state;
                std::shared_ptr<field> get_spawn_point();
            };
    }
}
}

#endif //CITY_DEFENCE_AI_H
