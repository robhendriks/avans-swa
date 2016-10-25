//
// Created by te on 25-Oct-16.
//

#include "base_gui.h"
namespace gui {
    base_gui::base_gui() {

    }

    void base_gui::init() {
        this->_renderer = renderer; // set renderer
        //TODO clear handlers
        this->set_handlers(); // set handlers
    }

    void base_gui::render(SDL_Renderer* renderer) {
        if(this->_init)
            this->init(renderer);
        this->update();
    }

    base_gui::~base_gui() {

    }
}