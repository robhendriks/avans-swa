//
// Created by robbie on 29-10-2016.
//

#include <boost/di.hpp>
#include "router.h"

namespace gui {
    router &router::get_instance() {
        static router instance;
        return instance;
    }

    void router::perform(int call) {
        if (m_action_map.find(m_current_action) != m_action_map.end()) {
            m_action_map[m_current_action](call);
            m_current_action_is_called = true;
        }
    }

    void router::on_event(engine::events::window_cleared &event) {
        perform(m_current_action_is_called ? 0 : -1);
    }

    void router::register_action(std::string name, std::function<void(int)> f) {
        m_action_map[name] = f;
    }

    void router::use(std::string action) {
        if (m_current_action != action) {
            // Let the controller we stop calling him
            perform(1);

            // Change the action
            m_current_action = action;
            m_current_action_is_called = false;
        }
    }

    void router::use_and_perform(std::string action) {
        use(action);
        perform(-1);
    }

    void router::use_and_perform_go_back(std::string action) {
        std::string original = m_current_action;
        m_current_action = action;
        perform(0);
        m_current_action = original;
    }

}
