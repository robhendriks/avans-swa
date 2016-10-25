//
// Created by te on 25-Oct-16.
//

#include "base_gui.h"
namespace gui {
    void base_gui::init(SDL_Renderer* renderer) {
        this->_renderer = renderer; // set renderer
        //TODO clear handlers
        this->set_handlers(); // set handlers
    }
}