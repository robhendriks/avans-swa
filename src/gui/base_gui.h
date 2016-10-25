//
// Created by te on 25-Oct-16.
//

#ifndef CITY_DEFENCE_BASE_GUI_H
#define CITY_DEFENCE_BASE_GUI_H
#include <SDL.h>
#include <memory>

namespace gui {
    class base_gui {
    public:
        virtual void render(SDL_Renderer* renderer);
        virtual ~base_gui();
    protected:
        SDL_Renderer* get_renderer();
    private:
        base_gui();
        virtual void update() = 0;
        virtual void init(SDL_Renderer* renderer) = 0;
        virtual void set_handlers() = 0;
        bool _init;
        SDL_Renderer* _renderer;
    };
}
#endif //CITY_DEFENCE_BASE_GUI_H
