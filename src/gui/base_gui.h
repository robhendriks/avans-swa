//
// Created by te on 25-Oct-16.
//

#ifndef CITY_DEFENCE_BASE_GUI_H
#define CITY_DEFENCE_BASE_GUI_H
#include <SDL.h>
#include <memory>
#include "../game/texture/texture_manager.h"

namespace gui {
    class base_gui {
    public:
        base_gui();
        virtual void render(game::texture::texture_manager* textureManager);
        virtual ~base_gui();
    protected:
        virtual void update() = 0;
        virtual void init(game::texture::texture_manager* textureManager);
        game::texture::texture_manager * get_texture_manager();
    private:
        virtual void set_handlers() = 0;
        bool _init;
        game::texture::texture_manager *_texture_manager;
    };
}
#endif //CITY_DEFENCE_BASE_GUI_H
