//
// Created by te on 25-Oct-16.
//

#ifndef CITY_DEFENCE_BASE_GUI_H
#define CITY_DEFENCE_BASE_GUI_H
#include <SDL.h>

namespace gui {
    class base_gui {
    public:
        virtual void init(SDL_Renderer* renderer);
        virtual void update() = 0;
    protected:
        SDL_Renderer* get_renderer();
    private:
        SDL_Renderer* _renderer;
        virtual void set_handlers();
    };
}
#endif //CITY_DEFENCE_BASE_GUI_H
