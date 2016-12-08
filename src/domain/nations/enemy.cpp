//
// Created by Mark on 21-11-2016.
//


#include <random>
#include "enemy.h"
namespace domain {
    namespace nations {
        enemy::enemy(std::string _name, int oppertunity_costs, bool _boss) {
            m_name = _name;
            m_oppertunity_cost =oppertunity_costs;
            m_boss = _boss;
            m_ai = nullptr;
        }

        enemy::enemy(std::string name, int min_damage, int max_damage, double attacks_per_second, int hitpoints, int granted_xp, int range, int movement, bool boss, std::shared_ptr<nation> nation, int oppertunity_costs) : m_destination(nullptr) {
            m_name = name;
            m_min_damage = min_damage;
            m_max_damage = max_damage;
            m_attack_speed = attacks_per_second;
            m_hp = hitpoints;
            m_granted_xp = granted_xp;
            m_range = range;
            m_movement = movement;
            m_boss = boss;
            m_nation = nation;
            m_oppertunity_cost = oppertunity_costs;
            m_ai = nullptr;
        }

        std::string enemy::get_name() {
            return m_nation.get()->get_prefix_name()+" - "+m_name;
        }


        int enemy::get_damage() {
            std::random_device rd; // obtain a random number from hardware
            std::mt19937 rnd(rd()); // seed the generator
            std::uniform_int_distribution<> damage(m_min_damage, m_max_damage);
            return damage(rnd);
        }

        double enemy::get_attack_speed(){
            return m_attack_speed;
        }

        int enemy::get_hp(){
            return m_hp;
        }

        int enemy::get_range(){
            return m_range;
        }
        int enemy::get_movement(){
            return m_movement;
        }
        int enemy::get_oppertunity_cost() const {
            return m_oppertunity_cost;
        }

        bool enemy::is_boss(){
            return m_boss;
        }

        int  enemy::lower_hitpoints(int points) {
            if(m_hp - points >= 0)
                m_hp -= points;
            else
                m_hp = 0;

            return m_hp;
        }

        enemy::~enemy() {

        }

        engine::math::box2_t enemy::get_box() const {
            return *m_destination;
        }

        void enemy::set_box(std::shared_ptr<engine::math::box2_t> destination) {
            m_destination = destination;
        }

        void enemy::update(unsigned int elapsed_time) {
            if(m_ai != nullptr){
                m_ai->update(elapsed_time);
            }
        }

        void enemy::set_ai(std::shared_ptr<domain::map::ai::ai> ai) {
            m_ai = ai;
        }

        bool operator<(const std::shared_ptr<enemy>&  s1, const std::shared_ptr<enemy>&  s2){

            return s1->get_oppertunity_cost() < s2->get_oppertunity_cost();
        }

    }
}
