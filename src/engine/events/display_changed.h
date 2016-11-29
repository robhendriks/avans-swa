//
// Created by robbie on 18-11-2016.
//

#ifndef CITY_DEFENCE_DISPLAY_CHANGE_H
#define CITY_DEFENCE_DISPLAY_CHANGE_H

#include "../math/box2.hpp"

namespace engine {
    namespace events {
        class display_changed {
        public:
            display_changed(math::box2_t box);
            math::box2_t get_display_box() const;
        private:
            math::box2_t m_box;
        };
    }
}


#endif //CITY_DEFENCE_DISPLAY_CHANGE_H
