//
// Created by te on 08-Dec-16.
//

#include "defender.h"

namespace domain {
    namespace combat {
        int defender::get_hp() {
            return m_hp;
        }


        int  defender::lower_hitpoints(int points) {
            if(m_hp - points >= 0)
                m_hp -= points;
            else
                m_hp = 0;

            return m_hp;
        }

        defender::defender(int hp, int granted_xp) {
            // a defender when 0 hp is dead
            if(m_hp <= 0){
                m_hp = 1;
            }
            else
                m_hp = hp;
            m_granted_xp = granted_xp;
        }
    }
}