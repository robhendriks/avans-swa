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

        using nation_ptr = std::shared_ptr<nation>;

        class enemy : public domain::combat::attacker, public domain::combat::defender {
        public:
            enemy(std::string name, int min_damage, int max_damage,
                  double attacks_per_second, int hitpoints, int granted_xp, int range,
                  int movement, bool boss, int oppertunity_costs);

            enemy(std::string name, int oppertunity_costs, bool boss);

            //Returns nationname + unitname
            std::string get_name();

            int get_oppertunity_cost() const;

            bool is_boss();

            virtual void set_box(std::shared_ptr<engine::math::box2_t> destination);

            virtual engine::math::box2_t get_box() const;

            void update(unsigned int elapsed_time);

            void set_ai(std::shared_ptr<domain::map::ai::ai> ai);

            virtual void draw(drawable::draw_managers_wrapper &draw_managers, unsigned int time_elapsed);

            virtual void set_draw_settings(std::string file_loc, engine::math::vec2_t image_start_position = {0, 0});

            nation_ptr get_nation() const;

            void set_nation(const nation_ptr &nation);

            ~enemy();

        private:
            std::shared_ptr<engine::math::box2_t> m_destination;
            std::string m_name;
            //Cost for using this enemy; to generate proper waves.
            int m_oppertunity_cost;
            bool m_boss;
            std::shared_ptr<domain::map::ai::ai> m_ai;
            nation_ptr m_nation;
        };

        bool operator<(const std::shared_ptr<enemy> &s1, const std::shared_ptr<enemy> &s2);
    }
}

#endif //CITY_DEFENCE_ENEMY_H
