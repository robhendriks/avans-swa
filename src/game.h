//
// Created by robbie on 5-11-2016.
//

#ifndef CITY_DEFENCE_GAME_H
#define CITY_DEFENCE_GAME_H

#include <memory>
#include "gui/views/base_view.h"
#include "engine/window.h"
#include "engine/events/display_changed.h"

class game {
public:
    game(engine::window &window);

    void update();

    void draw();

    void set_view(gui::views::base_view &view);

private:
    engine::window &m_window;
    gui::views::base_view *m_current_view;
};

using game_ptr = std::shared_ptr<game>;

#endif //CITY_DEFENCE_GAME_H
