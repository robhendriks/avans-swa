//
// Created by te on 09-Dec-16.
//
#include "ai_controlled.h"
#include "attacker.h"
#include "../map/ai/ai.h"
namespace domain {
    namespace combat {

        ai_controlled::ai_controlled() : m_ai(nullptr) {}

        void ai_controlled::set_ai(domain::map::ai::ai &ai) {
            m_ai = &ai;
        }

        domain::map::ai::ai *ai_controlled::get_ai() {
            return m_ai;
        }

        ai_controlled::~ai_controlled() {
            if (m_ai != nullptr) {
                delete m_ai;
            }
        }
    }
}
