//
// Created by robbie on 19-11-2016.
//

#include "game_tick.h"

namespace engine {
    namespace events {

        game_tick::game_tick(unsigned int tick_number, unsigned int game_time) : m_tick_number(tick_number),
            m_game_time(game_time) {

        }

        unsigned int game_tick::get_tick_number() const {
            return m_tick_number;
        }

        unsigned int game_tick::get_game_time() const {
            return m_game_time;
        }
    }
}
