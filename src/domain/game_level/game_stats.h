//
// Created by te on 18-Nov-16.
//

#ifndef CITY_DEFENCE_GAME_STATS_H
#define CITY_DEFENCE_GAME_STATS_H

namespace domain {
    namespace game_level {
        class game_stats{
        public:
            game_stats(long building_count = 0, long roads_count = 0, long max_duration = 0);
            void set_built_building_count(long count);
            long get_built_buildings_count();
            void set_built_roads_count(long count);
            long get_built_roads_count();
            void set_built_objects_count(long count);
            long get_built_objects_count();
            long get_max_duration();
            void set_max_duration(long duration);
            // duration not used in those operators. (reason being that if you for example did > then if your in the time limit it will say false because thats not bigger)
            bool operator==(const game_stats& other);
            bool operator!=(const game_stats& other);
            bool operator< (const game_stats& other);
            bool operator> (const game_stats& other);
            bool operator<=(const game_stats& other);
            bool operator>=(const game_stats& other);
            game_stats operator+(const game_stats& other);
        private:
            long m_built_buildings_count;
            long m_built_roads_count;
            long m_built_objects_count;
            long m_max_duration;
        };
    }
}
#endif //CITY_DEFENCE_GAME_STATS_H
