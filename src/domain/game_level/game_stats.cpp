//
// Created by te on 18-Nov-16.
//

#include "game_stats.h"
#include <algorithm>

namespace domain {
    namespace game_level {

        void game_stats::increase(std::string counter) {
            if (m_stats.find(counter) != m_stats.end()) {
                // Increase the current count
                m_stats[counter]++;
            } else {
                // Set a new count
                m_stats[counter] = 1;
            }
        }

        void game_stats::decrease(std::string counter) {
            if (m_stats.find(counter) != m_stats.end()) {
                // Decrease the current count
                m_stats[counter]--;
            } else {
                // Set a new count
                m_stats[counter] = -1;
            }
        }

        void game_stats::set_counter(std::string counter, int value) {
            m_stats[counter] = value;
        }

        int game_stats::get_count(std::string counter) const {
            if (m_stats.find(counter) != m_stats.end()) {
                return m_stats.at(counter);
            }

            return 0;
        }

        std::map<std::string, int> game_stats::get() const {
            return m_stats;
        }

        bool game_stats::operator==(const game_stats &other) {
            // Return always false when the stats are not equal of size
            if (m_stats.size() != other.m_stats.size()) {
                return false;
            }

            for (auto &counter : m_stats) {
                // Return false when the counter not exists in other or when the count is not equal
                if (other.m_stats.find(counter.first) == other.m_stats.end() || other.m_stats.at(counter.first) != counter.second) {
                    return false;
                }
            }

            return true;
        }

        bool game_stats::operator!=(const game_stats &other) {
            return !operator==(other);
        }

        bool game_stats::operator>(const game_stats &other) {
            return !operator<=(other);
        }

        bool game_stats::operator>=(const game_stats &other) {
            // Always false when the stats of this are less of size than other
            if (m_stats.size() < other.m_stats.size()) {
                return false;
            }

            // Check if all counters of other exists in this and if the count of it is at least equal
            for (auto &counter : other.m_stats) {
                // Return false when the counter not exists in other or when the count is less
                if (m_stats.find(counter.first) == m_stats.end() || m_stats[counter.first] < counter.second) {
                    return false;
                }
            }

            return true;
        }

        bool game_stats::operator<(const game_stats &other) {
            // Always true when the stats of this are less of size than other
            if (m_stats.size() < other.m_stats.size()) {
                return true;
            }

            // It's less when it's not equal or bigger
            return !operator>=(other);
        }

        bool game_stats::operator<=(const game_stats &other) {
            return operator<(other) || operator==(other);
        }

        game_stats game_stats::operator+(const game_stats &other) {
            game_stats stats;

            // Set the m_stats
            for (auto &counter : m_stats) {
                stats.set_counter(counter.first, counter.second);
            }

            // Add the stats of other
            for (auto &counter : other.m_stats) {
                if (stats.m_stats.find(counter.first) != stats.m_stats.end()) {
                    // Already exists
                    stats.set_counter(counter.first, stats.m_stats[counter.first] + counter.second);
                } else {
                    // New counter
                    stats.set_counter(counter.first, counter.second);
                }
            }

            return stats;
        }
    }
}
