//
// Created by robbie on 6-12-2016.
//

#ifndef CITY_DEFENCE_DRAW_MANAGERS_WRAPPER_H
#define CITY_DEFENCE_DRAW_MANAGERS_WRAPPER_H

#include "../../engine/graphics/texture_manager.h"
#include "../../engine/graphics/color_manager.h"
#include "../../engine/graphics/font_manager.h"

namespace domain {
    namespace drawable {
        struct draw_managers_wrapper {
            draw_managers_wrapper(engine::graphics::texture_manager &texture, engine::graphics::color_manager &color,
                engine::graphics::font_manager &font) : texture_manager(texture), color_manager(color),
                                                        font_manager(font) {}

            engine::graphics::texture_manager &texture_manager;
            engine::graphics::color_manager &color_manager;
            engine::graphics::font_manager &font_manager;
        };
    }
}


#endif //CITY_DEFENCE_DRAW_MANAGERS_WRAPPER_H
