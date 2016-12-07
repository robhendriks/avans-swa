//
// Created by Bert on 7-12-2016.
//

#ifndef CITY_DEFENCE_AI_H
#define CITY_DEFENCE_AI_H

#include "../field.h"


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
                void set_unit(std::shared_ptr<domain::nations::enemy> unit);
                void set_target(std::function< bool(domain::map::objects::field_object*) > target);
                bool is_initialised() const;

            private:
                int m_last_movement_time = 0;
                // to make sure you don't go back (maybe we want him to go back if building is placed behind him/
                // need to experiment
                std::shared_ptr<field> m_last_field;
                std::shared_ptr<field> m_current_field;
                std::shared_ptr<field> m_next_field;

                // this makes the ai a implentation that only works on field objects
                // in case it needs to work for enemies this needs to be moved to a sub class and this becomes a super and then a extra
                // implementation for get_target basically
                std::function< bool(domain::map::objects::field_object*) > m_is_target;
                // this one function needs to change so its not a field object but a "target' class that inherits from interface target
                domain::map::objects::field_object* m_current_target;
                // -----
                int m_last_attack_time = 0;


                std::shared_ptr<field> get_spawn_point();

                void move(unsigned int elapsed_time);
                std::shared_ptr<field> get_next_field();

                // this should be a super class of enemy and building(ms and damage needed only)
                std::shared_ptr<domain::map::map> m_map;
                std::shared_ptr<domain::nations::enemy> m_unit;
            };
    }
}
}

#endif //CITY_DEFENCE_AI_H
