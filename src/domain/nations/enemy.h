//
// Created by Mark on 21-11-2016.
//

#ifndef CITY_DEFENCE_ENEMY_H
#define CITY_DEFENCE_ENEMY_H

#include <string>
#include <memory>
#include "nation.h"

namespace domain {
    namespace nations {

        class enemy {
        public:
            enemy(std::string _name, int _mindamage, int _maxdamage, double _attackspersecond, int _hitpoints, int _grantedXP, int _range, int _movement, bool _boss, std::shared_ptr<nation> _nation, int _oppertunitycosts)
            ;

            enemy(std::string _name, int _oppertunitycosts, bool _boss);

            //Returns nationname + unitname
            std::string getName();

            //Returns a random number within the range of min & max damage
            int getDamage();

            double getattackspersecond();

            int getHitpoints();

            int getRange();
            int getMovement();
            int getOppertunity()const;

            bool getBoss();

            //Lowers hitpoints with the amount within the parameter; if 0 calls the delete method.
            //Returns the amount of XP.
            int lowerHitpoints(int points);
            ~enemy();



        private:
            std::string name;
            int mindamage;
            int maxdamage;

            //Cost for using this enemy; to generate proper waves.
            int oppertunitycosts;

            //Attacks per second
            double attackspersecond;
            int hitpoints;

            int grantedXP;

            //Range in tiles
            int range;

            //Tiles/second
            int movement;

            bool boss;

            //So we directly know which Nations this Unit belongs to.
            std::shared_ptr<nation> Nation;

        };

        bool operator<(const enemy &s1, const enemy &s2);
    }
}

#endif //CITY_DEFENCE_ENEMY_H
