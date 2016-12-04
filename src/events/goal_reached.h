//
// Created by robbie on 4-12-2016.
//

#ifndef CITY_DEFENCE_GOAL_REACHED_H
#define CITY_DEFENCE_GOAL_REACHED_H

#include <string>

namespace events {
    class goal_reached {
    public:
        goal_reached(std::string goal);
        std::string get_goal() const;

    private:
        std::string m_goal;
    };
}

#endif //CITY_DEFENCE_GOAL_REACHED_H
