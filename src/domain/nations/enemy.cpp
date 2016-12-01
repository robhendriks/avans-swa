//
// Created by Mark on 21-11-2016.
//


#include <random>
#include "enemy.h"
namespace domain {
    namespace nations {


        std::string enemy::getName() {
            return Nation.get()->getprefixname()+" - "+name;


        }


        int enemy::getDamage() {
            std::random_device rd; // obtain a random number from hardware
            std::mt19937 rnd(rd()); // seed the generator
            std::uniform_int_distribution<> damage(mindamage, maxdamage);
            return damage(rnd);
        }

        double enemy::getattackspersecond() {
            return attackspersecond;
        }

        int enemy::getHitpoints(){
            return hitpoints;
        }

        int enemy::getRange(){
            return range;
        }
        int enemy::getMovement(){
            return movement;
        }
        int enemy::getOppertunity()const {
            return oppertunitycosts;
        }

        bool enemy::getBoss(){
            return boss;
        }

        int  enemy::lowerHitpoints(int points){

            if(hitpoints <= points){
                delete this;
                return grantedXP;
            }
            else{
                hitpoints = hitpoints - points;
            }
            return 0;
        }

        enemy::enemy(const std::string &name, int mindamage, int maxdamage, int oppertunitycosts,
                     double attackspersecond, int hitpoints, int grantedXP, int range, int movement, bool boss,
                     const std::shared_ptr<nation> &Nation) : name(name), mindamage(mindamage), maxdamage(maxdamage),
                                                              oppertunitycosts(oppertunitycosts),
                                                              attackspersecond(attackspersecond), hitpoints(hitpoints),
                                                              grantedXP(grantedXP), range(range), movement(movement),
                                                              boss(boss), Nation(Nation) {}

        enemy::~enemy() {

        }
        bool operator<(const enemy &s1, const enemy &s2){
            return s1.getOppertunity() < s2.getOppertunity();
        }

    }
}
