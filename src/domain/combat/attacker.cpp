//
// Created by te on 08-Dec-16.
//

#include <random>
#include "attacker.h"
#include "../map/ai/ai.h"

namespace domain {
    namespace combat {
        attacker::attacker(int min_damage, int max_damage, double attackspeed, int range, int movement) :
            m_min_damage(min_damage), m_max_damage(max_damage), m_attack_speed(attackspeed), m_range(range),
            m_movement(movement), m_current_field(nullptr) {}

        attacker::attacker(const attacker &other) {
            m_min_damage = other.m_min_damage;
            m_max_damage = other.m_max_damage;
            m_attack_speed = other.m_attack_speed;
            m_range = other.m_range;
            m_movement = other.m_movement;
            m_current_field = nullptr;
        }

        domain::map::field *attacker::get_current_field() const {
            return m_current_field;
        }

        void attacker::set_current_field(domain::map::field &current_field) {
            m_current_field = &current_field;
        }

        int attacker::get_damage() const {
            std::random_device rd; // obtain a random number from hardware
            std::mt19937 rnd(rd()); // seed the generator
            std::uniform_int_distribution<> damage(m_min_damage, m_max_damage);
            return damage(rnd);
        }

        double attacker::get_attack_speed() const {
            return m_attack_speed;
        }

        int attacker::get_range() const {
            return m_range;
        }

        int attacker::get_movement() const {
            return m_movement;
        }

        int attacker::get_max_damage() const {
            return m_max_damage;
        }

        int attacker::get_min_damage() const {
            return m_min_damage;
        }

        void attacker::set_ai(domain::map::ai::ai &ai1) {
            ai1.set_unit(*this);
            ai_controlled::set_ai(ai1);
        }
    }
}
