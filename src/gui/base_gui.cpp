//
// Created by te on 25-Oct-16.
//

#include "base_gui.h"

namespace gui {
    base_gui::base_gui() {
    }

    void base_gui::init(game::texture::texture_manager* textureManager) {
        this->_texture_manager = textureManager;
        //TODO clear handlers
        this->set_handlers(); // set handlers
        this->_init = true;
    }

    void base_gui::render(game::texture::texture_manager* textureManager) {
        if(this->_init)
            this->init(textureManager);
        this->update();
    }

    base_gui::~base_gui() {

    }

    game::texture::texture_manager *base_gui::get_texture_manager(){
        return this->_texture_manager;
    }
}