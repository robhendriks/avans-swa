//
// Created by te on 19-Nov-16.
//

#ifndef CITY_DEFENCE_TRANSITION_LEVEL_MODEL_H
#define CITY_DEFENCE_TRANSITION_LEVEL_MODEL_H

#include "../../domain/gameworld/highscore.h"

namespace gui {
    namespace models {
        struct transition_level_model {
            transition_level_model() {};
            bool result;
            bool next_lvl_exists;
            int duration;
            std::vector<domain::gameworld::highscore*> highscores;

            void reset() {
                for (auto &highscore : highscores) {
                    delete highscore;
                }

                highscores.clear();
            }

            ~transition_level_model() {
                reset();
            }
        };
    }
}
#endif //CITY_DEFENCE_TRANSITION_LEVEL_MODEL_H
