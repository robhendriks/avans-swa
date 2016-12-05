//
// Created by robbie on 4-12-2016.
//

#include "goal_reached.h"

namespace events {

    goal_reached::goal_reached(std::string goal) : m_goal(goal) {

    }

    std::string goal_reached::get_goal() const {
        return m_goal;
    }
}
