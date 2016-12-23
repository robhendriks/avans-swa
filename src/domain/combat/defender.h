//
// Created by te on 08-Dec-16.
//

#ifndef CITY_DEFENCE_DEFENDER_H
#define CITY_DEFENCE_DEFENDER_H

#include "../drawable/drawable_game_object.h"

namespace domain {
    namespace combat {
        class defender : public virtual drawable::drawable_game_object {
        public:
            defender(int hp, int granted_xp);

            // Copy constructor
            defender(const defender& other);


            int get_max_hp();
            int get_current_hp();
            int get_current_hp_percentage_relative_to_max();

            //Lowers hitpoints with the amount within the parameter; limited to minimum 0
            virtual int lower_hitpoints(int points);

            virtual ~defender() {}

        private:
            // health points
            int m_max_hp;
            int m_current_hp;
            int m_granted_xp;
        };
    }
}

#endif //CITY_DEFENCE_DEFENDER_H
