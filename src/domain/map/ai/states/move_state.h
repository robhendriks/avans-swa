//
// Created by te on 08-Dec-16.
//

#ifndef CITY_DEFENCE_MOVE_STATE_H
#define CITY_DEFENCE_MOVE_STATE_H

#include "state.h"
#include "../../field.h"

namespace domain {
    namespace map {
        namespace ai {
            namespace states {
                class move_state : public state {
                public:
                    move_state();
                    void update(ai * ai, unsigned int elapsed_time);
                private:
                    int m_time_moved_on_current_field = -1;
                    // to make sure you don't go back (maybe we want him to go back if building is placed behind him/
                    // need to experiment
                    std::shared_ptr<field> m_last_field;
                    std::shared_ptr<field> m_next_field;

                    void move(ai * ai, unsigned int elapsed_time);
                    std::shared_ptr<field> get_next_field(domain::map::ai::ai *ai);
                };
            }
        }
    }
}

#endif //CITY_DEFENCE_MOVE_STATE_H
