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
            if(dynamic_cast<domain::combat::attacker*>(this) != nullptr){
                auto attacker = std::dynamic_pointer_cast<domain::combat::attacker>(shared_from_this());
                m_ai->set_unit(attacker);
                // TODO This should be removed because it should be set in json loader
                attacker->set_max_row(8);
                attacker->set_max_column(3);
            }
        }

        std::shared_ptr<domain::map::ai::ai> ai_controlled::get_ai() {
            return m_ai;
        }

        ai_controlled::~ai_controlled() {}

    }
}