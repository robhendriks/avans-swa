//
// Created by robbie on 7-11-2016.
//

#ifndef CITY_DEFENCE_MUSIC_STATE_H
#define CITY_DEFENCE_MUSIC_STATE_H

namespace engine {
    namespace audio {
        namespace music {
            enum state {
                PLAYING, PAUSED, NOT_PLAYING
            };
        }

        namespace sound {
            enum state {
                PLAYING, PAUSED
            };
        }
    }
}

#endif //CITY_DEFENCE_MUSIC_STATE_H
