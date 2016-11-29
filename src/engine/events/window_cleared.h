//
// Created by robbie on 29-10-2016.
//

#ifndef CITY_DEFENCE_WINDOW_CLEARED_H
#define CITY_DEFENCE_WINDOW_CLEARED_H

namespace engine {
    namespace events {
        class window_cleared {
        public:
            window_cleared(unsigned int time_elapsed, unsigned int game_ticks, float interpolation);
            float get_interpolation() const;
            unsigned int get_game_ticks() const;
            unsigned int get_time_elapsed() const;
        private:
            unsigned int m_time_elapsed;
            unsigned int m_game_ticks;
            float m_interpolation;
        };
    }
}

#endif //CITY_DEFENCE_WINDOW_CLEARED_H
