//
// Created by Mark on 21-11-2016.
//


#include <random>
#include "enemy.h"

namespace domain {
    namespace nations {
        enemy::enemy(std::string _name, int oppertunity_costs, bool _boss) : domain::combat::attacker(0, 0, 1, 1),
                                                                             domain::combat::defender(0, 0),
                                                                             m_destination(std::make_shared<engine::math::box2_t>(0, 0, 0, 0)) {
            m_name = _name;
            m_oppertunity_cost = oppertunity_costs;
            m_boss = _boss;
            m_ai = nullptr;
        }

        enemy::enemy(std::string name, int min_damage, int max_damage, double attacks_per_second, int hitpoints,
                     int granted_xp, int range, int movement, bool boss, int oppertunity_costs)
            : domain::combat::attacker(min_damage, max_damage, attacks_per_second, range, movement),
              domain::combat::defender(0, 0), m_destination(std::make_shared<engine::math::box2_t>(0, 0, 0, 0)) {
            m_name = name;
            m_boss = boss;
            m_oppertunity_cost = oppertunity_costs;
            m_ai = nullptr;
        }

        std::string enemy::get_name() {
            return m_nation->get_prefix() + " - " + m_name;
        }

        int enemy::get_oppertunity_cost() const {
            return m_oppertunity_cost;
        }

        bool enemy::is_boss() {
            return m_boss;
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
            if (m_ai != nullptr) {
                m_ai->update(elapsed_time);
            }
        }

        void enemy::set_ai(std::shared_ptr<domain::map::ai::ai> ai) {
            m_ai = ai;
        }

        void enemy::draw(drawable::draw_managers_wrapper &draw_managers, unsigned int time_elapsed) {
            domain::combat::attacker::draw(draw_managers, time_elapsed);
        }

        void enemy::set_draw_settings(std::string file_loc, engine::math::vec2_t image_start_position) {
            domain::combat::attacker::set_draw_settings(file_loc, image_start_position);
        }

        nation_ptr enemy::get_nation() const {
            return m_nation;
        }

        void enemy::set_nation(const nation_ptr &nation) {
            m_nation = nation;
        }

        bool operator<(const std::shared_ptr<enemy> &s1, const std::shared_ptr<enemy> &s2) {
            return s1->get_oppertunity_cost() < s2->get_oppertunity_cost();
        }

    }
}
