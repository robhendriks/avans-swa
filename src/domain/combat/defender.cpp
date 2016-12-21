//
// Created by te on 08-Dec-16.
//

#include "defender.h"

namespace domain {
    namespace combat {
        defender::defender(int current_hp, int granted_xp) {
            // a defender when 0 hp is dead
            if(m_current_hp <= 0){
                m_current_hp = 400;
            }
            else
                m_current_hp = current_hp;

            m_max_hp = m_current_hp;
            m_granted_xp = granted_xp;
        }

        defender::defender(const defender &other) {
            m_max_hp = other.m_max_hp;
            m_current_hp = other.m_current_hp;
            m_granted_xp = other.m_granted_xp;
        }

        int defender::get_current_hp() {
            return m_current_hp;
        }

        int  defender::lower_hitpoints(int points) {
            if(m_current_hp - points >= 0)
                m_current_hp -= points;
            else
                m_current_hp = 0;

            return m_current_hp;
        }

        int defender::get_max_hp() {
            return m_max_hp;
        }

        int defender::get_current_hp_percentage_relative_to_max() {
            if(m_current_hp == 0)
                return 0;

           return m_current_hp / m_max_hp * 100;
        }
    }
}
