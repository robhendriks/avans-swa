//
// Created by te on 09-Dec-16.
//
#include "ai_controlled.h"
#include "attacker.h"
#include "../map/ai/ai.h"
namespace domain {
    namespace combat {
        void ai_controlled::set_ai(std::shared_ptr<domain::map::ai::ai> ai) {
            m_ai = ai;

            auto attacker = dynamic_cast<domain::combat::attacker*>(this);
            if (attacker) {
                m_ai->set_unit(std::shared_ptr<domain::combat::attacker>(attacker));
            }
        }

        std::shared_ptr<domain::map::ai::ai> ai_controlled::get_ai() {
            return m_ai;
        }

        ai_controlled::~ai_controlled() {}

    }
}
