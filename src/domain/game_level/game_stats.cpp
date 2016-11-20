//
// Created by te on 18-Nov-16.
//

#include "game_stats.h"
namespace domain {
    namespace game_level {
        game_stats::game_stats(long building_count, long roads_count, long duration)
                : m_built_buildings_count(building_count), m_built_roads_count(roads_count), m_built_objects_count(m_built_buildings_count+m_built_roads_count), m_duration(duration) {

        }

        long game_stats::get_built_buildings_count() {
            return m_built_buildings_count;
        }

        long game_stats::get_built_roads_count() {
            return m_built_roads_count;
        }

        long game_stats::get_built_objects_count() {
            return m_built_objects_count;
        }

        long game_stats::get_duration() {
            return m_duration;
        }

        bool game_stats::operator==(const game_stats &other) {
            return (m_built_roads_count == other.m_built_roads_count &&
                    m_built_buildings_count == other.m_built_buildings_count &&
                    m_built_objects_count == other.m_built_objects_count);
        }


        bool game_stats::operator!=(const game_stats &other) {
            return !operator==(other);
        }

        bool game_stats::operator>(const game_stats &other) {
            return  !operator<(other);
        }

        bool game_stats::operator>=(const game_stats &other) {
            return operator>(other) || operator==(other);
        }

        bool game_stats::operator<(const game_stats &other) {
            return (m_built_roads_count < other.m_built_roads_count ||
                    m_built_buildings_count < other.m_built_buildings_count ||
                    m_built_objects_count < other.m_built_objects_count);
        }

        bool game_stats::operator<=(const game_stats &other) {
            return operator<(other) || operator==(other);
        }

        void game_stats::set_built_building_count(long count) {
            m_built_buildings_count = count;
        }

        void game_stats::set_built_roads_count(long count) {
            m_built_roads_count = count;
        }

        void game_stats::set_built_objects_count(long count) {
            m_built_objects_count = count;
        }

        game_stats game_stats::operator+(const game_stats &other) {
             return game_stats(m_built_buildings_count + other.m_built_buildings_count, m_built_roads_count + other.m_built_roads_count, m_duration + other.m_duration);
        }

        void game_stats::set_duration(long duration) {
            m_duration = duration;
        }

        void game_stats::set_start_duration(long duration) {
            m_start_duration = duration;
        }
    }
}