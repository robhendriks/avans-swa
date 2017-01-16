//
// Created by te on 09-Dec-16.
//

#ifndef CITY_DEFENCE_AI_CONTROLLED_H
#define CITY_DEFENCE_AI_CONTROLLED_H

#include <memory>

namespace domain {
    namespace map {
        namespace ai {
            class ai;
        }
    }
    namespace combat {
        class ai_controlled {
        public:
            ai_controlled();

            virtual void set_ai(domain::map::ai::ai &ai);

            domain::map::ai::ai *get_ai();

            ~ai_controlled();

        private:
            domain::map::ai::ai *m_ai;
        };
    }
}

#endif //CITY_DEFENCE_AI_CONTROLLED_H
