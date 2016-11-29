//
// Created by robbie on 19-11-2016.
//

#ifndef CITY_DEFENCE_GAME_TICK_H
#define CITY_DEFENCE_GAME_TICK_H

namespace engine {
    namespace events {
        class game_tick {
        public:
            game_tick(unsigned int tick_number, unsigned int game_time);
            unsigned int get_tick_number() const;
            unsigned int get_game_time() const;
        private:
            unsigned int m_tick_number;
            unsigned int m_game_time;
        };
    }
}


#endif //CITY_DEFENCE_GAME_TICK_H
