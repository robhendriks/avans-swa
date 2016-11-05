//
// Created by robbie on 4-11-2016.
//

#ifndef CITY_DEFENCE_BASE_CONTROLLER_H
#define CITY_DEFENCE_BASE_CONTROLLER_H

#include "../views/base_view.h"
#include "../../game.h"

namespace gui {
    namespace controllers {
        class base_controller {
        public:
            base_controller(game &game1);
            void view(gui::views::base_view &view);
        private:
            game &m_game;
        };
    }
}


#endif //CITY_DEFENCE_BASE_CONTROLLER_H
