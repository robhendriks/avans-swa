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

            auto self = shared_from_this();
            auto unit = std::dynamic_pointer_cast<domain::combat::attacker>(self);

            if (unit) {
                m_ai->set_unit(unit);
            }
        }

        std::shared_ptr<domain::map::ai::ai> ai_controlled::get_ai() {
            return m_ai;
        }

        ai_controlled::~ai_controlled() {}

    }
}
