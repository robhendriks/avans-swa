//
// Created by te on 25-Oct-16.
//

#ifndef CITY_DEFENCE_MENU_GUI_H
#define CITY_DEFENCE_MENU_GUI_H
#include "base_gui.h"

namespace gui{
    class menu_gui : public base_gui{
        public:
            menu_gui();
            void init(SDL_Renderer* renderer);
            void update();
            ~menu_gui();
        private:
            void set_handlers();
            SDL_Texture* _pTexture; // texture
            SDL_Rect _sourceRectangle; // the first rectangle
            SDL_Rect _destinationRectangle; // another rectangle
        };
}
#endif //CITY_DEFENCE_MENU_GUI_H
