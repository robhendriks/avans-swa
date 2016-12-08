//
// Created by te on 08-Dec-16.
//

#ifndef CITY_DEFENCE_DEFENDER_H
#define CITY_DEFENCE_DEFENDER_H

namespace domain {
    namespace combat {
        class defender {
        public:
            defender(int hp, int granted_xp);
            int get_hp();
            //Lowers hitpoints with the amount within the parameter; limited to minimum 0
            virtual int lower_hitpoints(int points);
            virtual ~defender() {}
        private:
            // health points
            int m_hp;
            int m_granted_xp;
        };
    }
}

#endif //CITY_DEFENCE_DEFENDER_H
