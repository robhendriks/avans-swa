//
// Created by Bert on 7-12-2016.
//

#ifndef CITY_DEFENCE_AI_H
#define CITY_DEFENCE_AI_H

#include "../field.h"
#include "states/state.h"
#include "../../combat/attacker.h"
#include "../../combat/defender.h"
#include <memory>


namespace domain {
    namespace nations {
        class enemy;
    }

    namespace map {
        namespace ai {

            enum state {
                DEAD, MOVE, SEARCH_AND_DESTROY
            };

            class ai {
            public:
                ai();

                ~ai();

                void update(unsigned int elapsed_time);

                void set_map(map &m_map);

                map &get_map() const;

                void set_unit(domain::combat::attacker &unit);

                domain::combat::attacker &get_unit();

                void set_new_target_func(std::function<domain::combat::defender *(domain::map::field *origin,
                                                                                  domain::map::ai::ai *ai)> target);

                std::function<domain::combat::defender *(domain::map::field *origin, domain::map::ai::ai *ai)>
                get_new_target_func();

                void set_animation_transition_func(std::function<void(std::string title, domain::map::ai::ai *ai,
                                                                      engine::math::box2_t &difference_between_you_and_target)> func);

                std::function<void(std::string title, domain::map::ai::ai *ai,
                                   engine::math::box2_t &difference_between_you_and_target)>
                get_animation_transition_func();

                bool is_initialised() const;

                void set_state(state state1);

                state get_current_state() const;

                field *get_current_field();

                void set_current_field(field &field);

                ai *clone();

            private:
                field *m_current_field;
                map *m_map;
                domain::combat::attacker *m_unit;
                std::function<domain::combat::defender *(domain::map::field *origin,
                                                         domain::map::ai::ai *ai)> m_new_target_func;
                std::function<void(std::string title, domain::map::ai::ai *ai,
                                   engine::math::box2_t &difference_between_you_and_target)> m_animation_transition_func;
                state m_state;

                field *get_spawn_point();

                std::map<state, states::state *> m_states;
            };
        }
    }
}

#endif //CITY_DEFENCE_AI_H
