//
// Created by te on 25-Oct-16.
//

#include "menu_gui.h"
namespace gui{
    menu_gui::menu_gui() {

    }

    void menu_gui::init(SDL_Renderer* renderer) {
        // set renderer and update the handlers using method set_handlers()
        base_gui::init(renderer);

        // image test
        this->_pTexture = IMG_LoadTexture("../../images/city-defense-logo.png");

        SDL_QueryTexture(this->_pTexture, NULL, &this->_sourceRectangle.w, NULL, &this->_sourceRectangle.h);
        _destinationRectangle.x = _sourceRectangle.x = 0;
        _destinationRectangle.y = _sourceRectangle.y = 0;
        _destinationRectangle.w = _sourceRectangle.w;
        _destinationRectangle.h = _sourceRectangle.h;

        SDL_RenderCopy(this->get_renderer(), this->_pTexture, &this->_sourceRectangle,
                       &this->_destinationRectangle);
    }

    void menu_gui::update() {

    }

    void menu_gui::set_handlers() {

    }

    menu_gui::~menu_gui() {

    }
}