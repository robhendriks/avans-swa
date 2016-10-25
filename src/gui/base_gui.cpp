//
// Created by te on 25-Oct-16.
//

#include "base_gui.h"
namespace gui {
    base_gui::base_gui() {

    }

    void base_gui::init(SDL_Renderer* renderer) {
        this->_renderer = renderer; // set renderer
        //TODO clear handlers
        this->set_handlers(); // set handlers
        this->_init = true;
    }

    SDL_Renderer* base_gui::get_renderer() {
        return this->_renderer;
    }

    void base_gui::render(SDL_Renderer* renderer) {
        if(this->_init)
            this->init(renderer);
        this->update();
    }

    base_gui::~base_gui() {

    }
}