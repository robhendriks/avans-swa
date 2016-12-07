//
// Created by Bert on 7-12-2016.
//

#ifndef CITY_DEFENCE_AI_H
#define CITY_DEFENCE_AI_H

#include "field.h"


namespace domain {
    namespace map {

        class ai {
        public:
            ai();
            ai(std::shared_ptr<map> current_map);
            std::shared_ptr<field> get_next_field(std::shared_ptr<field> current_field);
            std::shared_ptr<field> get_spawn_point(std::shared_ptr<map> current_map);
            std::shared_ptr<field> move(unsigned int elapsed_time);

            bool is_initialised() const;

        private:
            unsigned int m_last_movement_time = 0;
            long m_movement_time = 1000;
            std::shared_ptr<field> m_next_field;
            bool m_initialised = false;
        };
    }
}

#endif //CITY_DEFENCE_AI_H
