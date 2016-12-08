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

namespace domain {
    namespace nations {
        class enemy : public domain::drawable::drawable_game_object {
        public:
            enemy(std::string name, int min_damage, int max_damage,
                  double attacks_per_second, int hitpoints, int granted_xp, int range,
                  int movement, bool boss, std::shared_ptr<nation> nation, int oppertunity_costs);
            enemy(std::string name, int oppertunity_costs, bool boss);
            //Returns nationname + unitname
            std::string get_name();
            //Returns a random number within the range of min & max damage
            int get_damage();
            double get_attack_speed();
            int get_hp();
            int get_range();
            int get_movement();
            int get_oppertunity_cost()const;
            bool is_boss();
            //Lowers hitpoints with the amount within the parameter; limited to minimum 0
            int lower_hitpoints(int points);
            virtual void set_box(std::shared_ptr<engine::math::box2_t> destination);
            virtual engine::math::box2_t get_box() const;
            void update(unsigned int elapsed_time);
            void set_ai(std::shared_ptr<domain::map::ai::ai> ai);
            ~enemy();
        private:
            std::shared_ptr<engine::math::box2_t> m_destination;
            std::string m_name;
            int m_min_damage;
            int m_max_damage;
            //Cost for using this enemy; to generate proper waves.
            int m_oppertunity_cost;
            //Attacks per second
            double m_attack_speed;
            // health points
            int m_hp;
            int m_granted_xp;
            //Range in tiles
            int m_range;
            //% of a tile per sec
            int m_movement;
            bool m_boss;
            std::shared_ptr<domain::map::ai::ai> m_ai;
            std::shared_ptr<nation> m_nation;
        };

        bool operator<(const std::shared_ptr<enemy> &s1, const std::shared_ptr<enemy>  &s2);
    }
}

#endif //CITY_DEFENCE_ENEMY_H
