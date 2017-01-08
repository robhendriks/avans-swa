//
// Created by robbie on 8-1-2017.
//

#ifndef CITY_DEFENCE_HIGHSCORES_H
#define CITY_DEFENCE_HIGHSCORES_H

#include <ctime>

namespace domain {
    namespace gameworld {
        class highscore {
        public:
            highscore(unsigned int score, time_t time);

            unsigned int get_score() const;

            time_t get_time() const;

            bool operator < (const highscore &other) const;

        private:
            unsigned int m_score;
            time_t m_time;
        };
    }
}

#endif //CITY_DEFENCE_HIGHSCORES_H
