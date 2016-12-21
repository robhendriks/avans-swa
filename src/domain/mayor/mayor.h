//
// Created by te on 20-Dec-16.
//

#ifndef CITY_DEFENCE_MAYOR_H
#define CITY_DEFENCE_MAYOR_H

#include <queue>
#include "../drawable/drawable_game_object.h"
#include "../game_level/game_stats.h"
#include "../../engine/observer/observer.h"

namespace domain{
    struct milestone{
        int min;
        int max;
        std::vector<std::string> responses;
        bool reached;
    };

    struct milestone_group{
        std::string display_name;
        std::string counter_name;
        std::vector<milestone> milestones;
    };

    class mayor : engine::observer::observer<domain::game_level::game_stats>{
    public:
        mayor();
        mayor(std::string name, std::vector<std::string> hobbies, std::vector<std::string> behavior);

        // should be called each time a mayor gets added to a new stat to avoid overflowing the queue with events that have been
        // reached at the start
        void init(game_level::game_stats* init);

        void notify(game_level::game_stats *p_observee, std::string title);
        std::string get_name() const;
        std::vector<std::string> get_behavior() const;
        void set_behavior(std::vector<std::string> behavior);
        std::vector<std::string> get_hobbies() const;
        void set_hobbies(std::vector<std::string> hobbies);
        // stone group already exists with the same now it will be overwritten
        void add_milestone_group(milestone_group group);
        void add_milestone_groups(std::vector<milestone_group> groups);
        // returns a milestone_group with NA as countername in case none are found
        const milestone_group get_milestone_group(std::string counter_name);
    private:
        // properties
        std::string m_name;
        std::vector<std::string> m_behavior;
        std::vector<std::string> m_hobbies;

        // milestones
        std::map <std::string, milestone_group> m_milestone_groups;
        std::queue<milestone> m_queue;

        // for display
        milestone m_current_shown_milestone;
        int m_current_shown_response = -1;
        long last_time_current_milestone_shown = -1;

        // update gets called every notify
        void update(game_level::game_stats *p_observee, std::string title);

        // to avoid having the queue filled when first init
        void setup(game_level::game_stats* init);
        // get the new reached milestones (also sets them automatically to reached = true
        std::vector<milestone> get_new_reached_milestones(game_level::game_stats* game_stats, std::string counter_name = "");
        int get_response_index(milestone mile_stone);
    };
}

#endif //CITY_DEFENCE_MAYOR_H
