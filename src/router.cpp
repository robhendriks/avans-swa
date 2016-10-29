//
// Created by robbie on 29-10-2016.
//

#include <boost/di.hpp>
#include "router.h"


router &router::get_instance() {
    static router instance;
    return instance;
}

void router::on_event(engine::events::window_cleared &event) {
    if (m_action_map.find(current_action) != m_action_map.end()) {
        m_action_map[current_action]();
    }
}

void router::register_action(std::string name, std::function<void()> f) {
    m_action_map[name] = f;
}

void router::use(std::string action) {
    current_action = action;
}
