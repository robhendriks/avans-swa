//
// Created by robbie on 29-10-2016.
//

#ifndef CITY_DEFENCE_GAME_H
#define CITY_DEFENCE_GAME_H


#include "engine/events/window_cleared.h"
#include "engine/eventbus/subscriber.h"
#include <functional>
#include <map>

class router : public engine::eventbus::subscriber<engine::events::window_cleared> {
public:
    static router& get_instance();

    void perform();
    void on_event(engine::events::window_cleared &event);

    void register_action(std::string name, std::function<void()> f);
    void use(std::string action);
    void use_and_perform(std::string action);

private:
    router() {};

    router(router const&) = delete;
    void operator=(router const&) = delete;

    std::map<std::string, std::function<void()>> m_action_map;
    std::string current_action;
};


#endif //CITY_DEFENCE_GAME_H
