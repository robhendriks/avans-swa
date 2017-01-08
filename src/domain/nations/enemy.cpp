#include <random>
#include "enemy.h"
namespace domain {
    namespace nations {
        enemy::enemy(std::string name, int min_damage, int max_damage, double attacks_per_second, int hitpoints, int granted_xp,
                     int range, int movement, bool boss, nation &nation1, int oppertunity_costs)
                :  domain::combat::attacker(min_damage, max_damage, attacks_per_second, range, movement),
                   domain::combat::defender(hitpoints, granted_xp),
                   m_destination({0,0},{0,0}), m_name(name), m_oppertunity_cost(oppertunity_costs), m_boss(boss),
                   m_disposed(false), m_nation(&nation1) {}

        // Copy constructor
        enemy::enemy(const enemy &other) :
            domain::drawable::drawable_game_object(other), domain::combat::attacker::attacker(other),
            domain::combat::defender::defender(other), m_destination(other.m_destination), m_nation(other.m_nation) {
            m_name = other.m_name;
            m_oppertunity_cost = other.m_oppertunity_cost;
            m_boss = other.m_boss;
        }

        void enemy::dispose() {
            m_disposed = true;
        }

        std::string enemy::get_name() {
            return m_nation->get_prefix_name() + " - " + m_name;
        }

        int enemy::get_oppertunity_cost() const {
            return m_oppertunity_cost;
        }

        bool enemy::is_boss() const {
            return m_boss;
        }

        bool enemy::is_disposed() const {
            return m_disposed;
        }

        engine::math::box2_t enemy::get_box() const {
            return m_destination;
        }

        void enemy::set_box(engine::math::box2_t destination) {
            m_destination = destination;
        }

        void enemy::update(unsigned int elapsed_time) {
            if(get_ai() != nullptr){
                get_ai()->update(elapsed_time);
            }
        }

        bool operator<(const enemy&  s1, const enemy&  s2){
            return s1.get_oppertunity_cost() < s2.get_oppertunity_cost();
        }

        enemy::~enemy() {
        }

        enemy *enemy::clone() const {
            return new enemy(*this);
        }

        void enemy::set_nation(nation &nation1) {
            m_nation = &nation1;
        }
    }
}
