//
// Created by robbie on 5-11-2016.
//

#ifndef CITY_DEFENCE_GAME_H
#define CITY_DEFENCE_GAME_H


#include "gui/views/base_view.h"

class game : public engine::eventbus::subscriber<engine::events::window_cleared> {
public:
    void on_event(engine::events::window_cleared &event);
    void use_view(gui::views::base_view &view);
private:
    gui::views::base_view *m_current_view;
};


#endif //CITY_DEFENCE_GAME_H
