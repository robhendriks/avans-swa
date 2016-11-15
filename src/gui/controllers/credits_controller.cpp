//
// Created by robbie on 14-11-2016.
//

#include "credits_controller.h"

gui::controllers::credits_controller::credits_controller(views::credits &view, game &game1) :
    base_controller(game1), m_view(view) {

}

void gui::controllers::credits_controller::show() {
    view(m_view);
}
