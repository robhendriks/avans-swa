//
// Created by te on 25-Oct-16.
//
#include <SDL_image.h>
#include "menu_gui.h"
namespace gui{
    menu_gui::menu_gui()  {
    }

    void menu_gui::init(game::texture::texture_manager* textureManager) {
        // set renderer and update the handlers using method set_handlers()
        base_gui::init(textureManager);

        this->get_texture_manager()->load_texture("images/menu.png", "menu_item_1" );
    }

    void menu_gui::update() {
        this->get_texture_manager()->draw("menu_item_1", 0, 0, 339, 122, 150,0);
        this->get_texture_manager()->draw("menu_item_1", 0, 122, 339, 122, 150,122);
        this->get_texture_manager()->draw("menu_item_1", 0, 244, 339, 122, 150,244);
    }

    void menu_gui::set_handlers() {

    }

    menu_gui::~menu_gui() {

    }
}