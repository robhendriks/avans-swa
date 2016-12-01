//
// Created by Mark on 21-11-2016.
//

#ifndef CITY_DEFENCE_ENEMY_H
#define CITY_DEFENCE_ENEMY_H

#include <string>
#include <memory>
#include "nation.h"
#include "../drawable/drawable_game_object.h"

namespace domain {
    namespace nations {
        class enemy : public domain::drawable::drawable_game_object {
        public:

            enemy(std::string _name, double _movement, int _min_damge, int _max_damage, int _hitpoints,
                  std::string type, std::shared_ptr<nation> _nation,
                  int _oppertunitycosts);

            enemy(const std::string &name, int mindamage, int maxdamage, int oppertunitycosts, double attackspersecond,
                  int hitpoints, int grantedXP, int range, int movement, bool boss,
                  const std::shared_ptr<nation> &Nation);

            enemy(std::string _name, int _oppertunitycosts, bool _boss);

            //Returns nationname + unitname
            std::string getName();

            //Returns a random number within the range of min & max damage
            int getDamage();

            double getattackspersecond();

            int getHitpoints();

            int getRange();

            int getMovement();

            int getOppertunity() const;

            bool getBoss();

            //Lowers hitpoints with the amount within the parameter; if 0 calls the delete method.
            //Returns the amount of XP.
            int lowerHitpoints(int points);

            ~enemy();

            virtual engine::math::box2_t get_box() const;

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

        bool operator<(const std::shared_ptr<enemy> &s1, const std::shared_ptr<enemy>  &s2);
    }
}

#endif //CITY_DEFENCE_ENEMY_H
