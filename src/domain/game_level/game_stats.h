//
// Created by te on 18-Nov-16.
//

#ifndef CITY_DEFENCE_GAME_STATS_H
#define CITY_DEFENCE_GAME_STATS_H

#include <memory>
#include <vector>
#include <map>
#include "game_stats_modifier.h"

namespace domain {
    namespace game_level {
        class game_stats {
        public:
            /**
             *
             * @param max_duration - use -1 for an infinite duration
             */
            game_stats(long max_duration = -1);

            /**
             * Get the setted duration
             * @return
             */
            long get_max_duration();

            /**
             * Set the duration
             * @param duration
             */
            void set_max_duration(long duration);

            /**
             * Increase a counter
             *
             * @param counter
             */
            void increase(std::string counter);

            /**
             * Decrease a counter
             *
             * @param counter
             */
            void decrease(std::string counter);

            /**
             * Set a counter
             *
             * @param counter
             * @param value
             */
            void set_counter(std::string counter, int value);

            /**
             * Get the count
             *
             * @param counter
             */
            int get_count(std::string counter) const;

            /**
             * Get the game_stats
             *
             * @return
             */
            std::map<std::string, int> get() const;

            // max duration not used in those operators. (reason being that if you for example did > then if your in the time limit it will say false because thats not bigger)
            bool operator==(const game_stats& other);
            bool operator!=(const game_stats& other);
            bool operator< (const game_stats& other);
            bool operator> (const game_stats& other);
            bool operator<=(const game_stats& other);
            bool operator>=(const game_stats& other);
            game_stats operator+(const game_stats& other);
        private:
            long m_max_duration;
            std::map<std::string, int> m_stats;
        };
    }
}
#endif //CITY_DEFENCE_GAME_STATS_H
