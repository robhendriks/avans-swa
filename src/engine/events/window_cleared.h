//
// Created by robbie on 29-10-2016.
//

#ifndef CITY_DEFENCE_WINDOW_CLEARED_H
#define CITY_DEFENCE_WINDOW_CLEARED_H

namespace engine {
    namespace events {
        class window_cleared {
        public:
            window_cleared(float interpolation);
            float get_interpolation() const;
        private:
            float m_interpolation;
        };
    }
}

#endif //CITY_DEFENCE_WINDOW_CLEARED_H
