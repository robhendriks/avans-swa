//
// Created by te on 08-Dec-16.
//

#ifndef CITY_DEFENCE_ATTACKER_H
#define CITY_DEFENCE_ATTACKER_H

#include "../drawable/drawable_game_object.h"
#include "ai_controlled.h"
#include "../map/field.h"

namespace domain {
    namespace combat {
        class attacker : public virtual drawable::drawable_game_object, public ai_controlled {
        public:
            attacker(int min_damage, int max_damage, double attackspeed, int range, int movement = 0);

            // Copy constructor
            attacker(const attacker& other);

            //Returns a random number within the range of min & max damage
            int get_damage();

            double get_attack_speed();

            int get_range();

            int get_movement();

            std::shared_ptr<domain::map::field> get_current_field() const;

            void set_current_field(const std::shared_ptr<domain::map::field> &current_field);

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

            std::shared_ptr<domain::map::field> m_current_field;
        };
    }
}


#endif //CITY_DEFENCE_ATTACKER_H
