//
// Created by te on 08-Dec-16.
//

#ifndef CITY_DEFENCE_ATTACKER_H
#define CITY_DEFENCE_ATTACKER_H

#include "../drawable/drawable_game_object.h"
#include "ai_controlled.h"

namespace domain{
    namespace combat{
        class attacker :  public drawable::drawable_game_object, public ai_controlled {
        public:
            attacker(int min_damage, int max_damage, double attackspeed, int range, int movement = 0);
            //Returns a random number within the range of min & max damage
            int get_damage();
            double get_attack_speed();
            int get_range();
            int get_movement();
            virtual ~attacker() {}
        private:
            int m_min_damage;
            int m_max_damage;
            //Attacks per second
            double m_attack_speed;
            //Range in tiles
            int m_range;
            //% of a tile per sec
            int m_movement;
        };
    }
}



#endif //CITY_DEFENCE_ATTACKER_H
