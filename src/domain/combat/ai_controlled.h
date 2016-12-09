//
// Created by te on 09-Dec-16.
//

#ifndef CITY_DEFENCE_AI_CONTROLLED_H
#define CITY_DEFENCE_AI_CONTROLLED_H

#include <memory>

namespace domain {
    namespace map{
        namespace ai{
            class ai;
        }
    }
    namespace combat {
        class ai_controlled : public std::enable_shared_from_this<ai_controlled>{
        public:
            void set_ai(std::shared_ptr<domain::map::ai::ai> ai);
            std::shared_ptr<domain::map::ai::ai> get_ai();
            virtual ~ai_controlled();
        private:
            std::shared_ptr<domain::map::ai::ai> m_ai;
        };
    }
}

#endif //CITY_DEFENCE_AI_CONTROLLED_H
