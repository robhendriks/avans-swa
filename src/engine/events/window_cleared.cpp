//
// Created by robbie on 29-10-2016.
//

#include "window_cleared.h"

namespace engine {
    namespace events {

        window_cleared::window_cleared(unsigned int time_elapsed, unsigned int game_ticks, float interpolation) :
            m_time_elapsed(time_elapsed), m_game_ticks(game_ticks), m_interpolation(interpolation) {
        }

        float window_cleared::get_interpolation() const {
            return m_interpolation;
        }

        unsigned int window_cleared::get_game_ticks() const {
            return m_game_ticks;
        }

        unsigned int window_cleared::get_time_elapsed() const {
            return m_time_elapsed;
        }
    }
}
