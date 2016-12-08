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

        using nation_ptr = std::shared_ptr<nation>;

        class enemy : public domain::drawable::drawable_game_object {
        public:
            enemy(std::string _name, int _mindamage, int _maxdamage, double _attackspersecond, int _hitpoints,
                  int _grantedXP, int _range, double _movement, bool _boss, int _oppertunitycosts);

            enemy(std::string _name, int _oppertunitycosts, bool _boss);

            //Returns nationname + unitname
            std::string getName();

            //Returns a random number within the range of min & max damage
            int getDamage();

            double getattackspersecond();

            int getHitpoints();

            int getRange();

            double getMovement();

            int getOppertunity() const;

            bool getBoss();

            //Lowers hitpoints with the amount within the parameter; if 0 calls the delete method.
            //Returns the amount of XP.
            int lowerHitpoints(int points);

            ~enemy();

            virtual void set_box(std::shared_ptr<engine::math::box2_t> destination);

            virtual engine::math::box2_t get_box() const;

            const nation_ptr &get_nation() const;

            void set_nation(const nation_ptr &nation);

        private:
            std::shared_ptr<engine::math::box2_t> m_destination;

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
            double movement;

            bool boss;

            //So we directly know which Nations this Unit belongs to.
            nation_ptr m_nation;
        };

        bool operator<(const std::shared_ptr<enemy> &s1, const std::shared_ptr<enemy> &s2);
    }
}

#endif //CITY_DEFENCE_ENEMY_H
