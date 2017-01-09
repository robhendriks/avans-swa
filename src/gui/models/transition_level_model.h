//
// Created by te on 19-Nov-16.
//

#ifndef CITY_DEFENCE_TRANSITION_LEVEL_MODEL_H
#define CITY_DEFENCE_TRANSITION_LEVEL_MODEL_H

#include "../../domain/gameworld/highscore.h"

namespace gui {
    namespace models {
        struct transition_level_model {
        public:
            transition_level_model() {};
            bool result;
            bool next_lvl_exists;
            int duration;

            std::vector<domain::gameworld::highscore> highscores;

            void set_highscores(std::vector<domain::gameworld::highscore*> highscores1) {
                highscores_ptrs = highscores1;

                for (auto &h : highscores1) {
                    highscores.push_back(*h);
                }

                std::sort(highscores.begin(), highscores.end());
                std::reverse(highscores.begin(), highscores.end());
            }

            void reset() {
                for (auto &highscore : highscores_ptrs) {
                    delete highscore;
                }

                highscores_ptrs.clear();
                highscores.clear();
            }

            ~transition_level_model() {
                reset();
            }

        private:
            std::vector<domain::gameworld::highscore*> highscores_ptrs;
        };
    }
}
#endif //CITY_DEFENCE_TRANSITION_LEVEL_MODEL_H
