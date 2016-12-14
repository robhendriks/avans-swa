//
// Created by Mark on 21-11-2016.
//

#ifndef CITY_DEFENCE_ENEMY_H
#define CITY_DEFENCE_ENEMY_H

#include <string>
#include <memory>
#include "nation.h"
#include "../drawable/drawable_game_object.h"
#include "../map/ai/ai.h"
#include "../combat/attacker.h"
#include "../combat/defender.h"

namespace domain {
    namespace nations {
        class enemy : public domain::combat::attacker, public domain::combat::defender {
        public:
            enemy(std::string name, int min_damage, int max_damage,
                  double attacks_per_second, int hitpoints, int granted_xp, int range,
                  int movement, bool boss, std::shared_ptr<nation> nation, int oppertunity_costs);

            // Copy constructor
            enemy(const enemy& other);

            //Returns nationname + unitname
            std::string get_name();

            int get_oppertunity_cost() const;

            bool is_boss();

            virtual void set_box(std::shared_ptr<engine::math::box2_t> destination);

            virtual engine::math::box2_t get_box() const;

            void update(unsigned int elapsed_time);

            ~enemy();

        private:
            std::shared_ptr<engine::math::box2_t> m_destination;
            std::string m_name;
            //Cost for using this enemy; to generate proper waves.
            int m_oppertunity_cost;
            bool m_boss;
            std::shared_ptr<nation> m_nation;
        };

        bool operator<(const std::shared_ptr<enemy> &s1, const std::shared_ptr<enemy> &s2);
    }
}

#endif //CITY_DEFENCE_ENEMY_H
