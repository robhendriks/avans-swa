#include <random>
#include "enemy.h"
namespace domain {
    namespace nations {
        enemy::enemy(std::string name, int min_damage, int max_damage, double attacks_per_second, int hitpoints, int granted_xp,
                     int range, int movement, bool boss, std::shared_ptr<nation> nation, int oppertunity_costs)
                :  domain::combat::attacker(min_damage, max_damage, attacks_per_second, range, movement),
                   domain::combat::defender(hitpoints, granted_xp),
                   m_destination(std::make_shared<engine::math::box2_t>(engine::math::box2_t({0,0},{0,0}))), m_name(name), m_oppertunity_cost(oppertunity_costs), m_boss(boss), m_nation(nation){}

        std::string enemy::get_name() {
            return m_nation.get()->get_prefix_name()+" - "+m_name;
        }
        int enemy::get_oppertunity_cost() const {
            return m_oppertunity_cost;
        }

        bool enemy::is_boss(){
            return m_boss;
        }

        engine::math::box2_t enemy::get_box() const {
            return *m_destination;
        }

        void enemy::set_box(std::shared_ptr<engine::math::box2_t> destination) {
            m_destination = destination;
        }

        void enemy::update(unsigned int elapsed_time) {
            if(get_ai() != nullptr){
                get_ai()->update(elapsed_time);
            }
        }

        bool operator<(const std::shared_ptr<enemy>&  s1, const std::shared_ptr<enemy>&  s2){
            return s1->get_oppertunity_cost() < s2->get_oppertunity_cost();
        }

        enemy::~enemy() {
        }
    }
}
