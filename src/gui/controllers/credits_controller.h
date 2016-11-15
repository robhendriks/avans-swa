//
// Created by robbie on 14-11-2016.
//

#ifndef CITY_DEFENCE_CREDITS_CONTROLLER_H
#define CITY_DEFENCE_CREDITS_CONTROLLER_H

#include "base_controller.h"
#include "../views/credits.h"

namespace gui {
    namespace controllers {
        class credits_controller : public base_controller {
        public:
            credits_controller(views::credits &view, game &game1);
            void show();

        private:
            views::credits &m_view;
        };
    }
}

#endif //CITY_DEFENCE_CREDITS_CONTROLLER_H
