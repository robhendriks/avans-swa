//
// Created by te on 08-Dec-16.
//

#include "defender.h"

namespace domain {
    namespace combat {
        defender::defender(int hp, int granted_xp) {
            // a defender when 0 hp is dead
            if(m_hp <= 0){
                m_hp = 400;
            }
            else
                m_hp = hp;
            m_granted_xp = granted_xp;
        }

        defender::defender(const defender &other) : domain::drawable::drawable_game_object(other) {
            m_hp = other.m_hp;
            m_granted_xp = other.m_granted_xp;
        }

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
    }
}
