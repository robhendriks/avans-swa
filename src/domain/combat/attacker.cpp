//
// Created by te on 08-Dec-16.
//

#include <random>
#include "attacker.h"

namespace domain {
    namespace combat {
        attacker::attacker(int min_damage, int max_damage, double attackspeed, int range, int movement) : m_min_damage(
            min_damage),
                                                                                                          m_max_damage(
                                                                                                              max_damage),
                                                                                                          m_attack_speed(
                                                                                                              attackspeed),
                                                                                                          m_range(
                                                                                                              range),
                                                                                                          m_movement(
                                                                                                              movement) {}

        attacker::attacker(const attacker &other) {
            m_min_damage = other.m_min_damage;
            m_max_damage = other.m_max_damage;
            m_attack_speed = other.m_attack_speed;
            m_range = other.m_range;
            m_movement = other.m_movement;
        }

        std::shared_ptr<domain::map::field> attacker::get_current_field() const {
            return m_current_field;
        }

        void attacker::set_current_field(const std::shared_ptr<domain::map::field> &current_field) {
            m_current_field = current_field;
        }

        int attacker::get_damage() {
            std::random_device rd; // obtain a random number from hardware
            std::mt19937 rnd(rd()); // seed the generator
            std::uniform_int_distribution<> damage(m_min_damage, m_max_damage);
            return damage(rnd);
        }

        double attacker::get_attack_speed() {
            return m_attack_speed;
        }

        int attacker::get_range() {
            return m_range;
        }

        int attacker::get_movement() {
            return m_movement;
        }
    }
}
