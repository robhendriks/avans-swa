//
// Created by robbie on 4-11-2016.
//

#include "base_controller.h"

namespace gui {
    namespace controllers {

        base_controller::base_controller(game &game1) : m_game(game1) {
        }

        void base_controller::view(gui::views::base_view &view) {
            m_game.use_view(view);
        }
    }
}
