//
// Created by robbie on 8-1-2017.
//

#include "highscore.h"

namespace domain {
    namespace gameworld {

        highscore::highscore(unsigned int score, time_t time) : m_score(score), m_time(time) {}

        unsigned int highscore::get_score() const {
            return m_score;
        }

        time_t highscore::get_time() const {
            return m_time;
        }

        bool highscore::operator< (const highscore &other) const {
            return (m_score < other.m_score);
        }
    }
}
