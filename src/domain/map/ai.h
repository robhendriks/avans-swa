//
// Created by Bert on 7-12-2016.
//

#ifndef CITY_DEFENCE_AI_H
#define CITY_DEFENCE_AI_H

#include "field.h"


namespace domain {
    namespace nation{
        class enemy;
    }

    namespace map {

        class ai {
        public:
            ai();
            ai(std::shared_ptr<map> current_map, std::shared_ptr<domain::nation::enemy> enemy);


            void set_map(std::shared_ptr<map> map);
            void set_unit(std::shared_ptr<domain::nation::enemy> unit);
            bool is_initialised() const;

        private:
            unsigned int m_last_movement_time = 0;
            long m_movement_time = 1000;

            std::shared_ptr<field> m_current_field;
            std::shared_ptr<field> m_next_field;

            std::shared_ptr<field> get_next_field(std::shared_ptr<field> current_field);
            std::shared_ptr<field> get_spawn_point();
            std::shared_ptr<field> move(unsigned int elapsed_time);

            // this should be a super class of enemy and building(ms and damage needed only)
            std::shared_ptr<domain::map::map> m_map;
            std::shared_ptr<domain::nation::enemy> m_unit;
        };
    }
}

#endif //CITY_DEFENCE_AI_H
