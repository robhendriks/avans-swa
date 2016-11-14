//
// Created by te on 10-Nov-16.
//

#ifndef CITY_DEFENCE_DRAWABLE_GAME_OBJECT_H
#define CITY_DEFENCE_DRAWABLE_GAME_OBJECT_H


#include "../../engine/math/box2.hpp"
#include "../../engine/graphics/texture_manager.h"
#include "abstract_drawable_game_object.h"
#include <memory>
namespace domain {
    namespace drawable {
        class drawable_game_object : public abstract_drawable_game_object {
        public:
            drawable_game_object(std::string id, std::string file_loc, engine::math::vec2_t *image_start_position,
                                 int rotation = 0);

            // can be overwritten in case you don't want to load the textures of the current object because there is a chance
            // you won't draw them but only of a child object. (if overwritten no call will be made to draw_object)
            virtual void draw(engine::graphics::texture_manager &texture_manager, engine::math::box2_t &dest);

            // override in case something else gets drawn instead of only itself
            virtual void unload(engine::graphics::texture_manager &texture_manager);

        protected:
            SDL_Texture *texture;

            std::string id;
            std::string file_loc;
            std::unique_ptr<engine::math::vec2_t> image_start_position;
            int rotation;

            // load texture of current object in case its not loaded in yet. (this will fill texture field or give a exception
            void load_texture_if_not_loaded_yet(engine::graphics::texture_manager &texture_manager);

        private:
            // basic implementation is to draw the current object (needs to be overwritten for also drawing children)
            virtual void draw_object(engine::graphics::texture_manager &texture_manager, engine::math::box2_t &dest);
        };
    }
}

#endif //CITY_DEFENCE_DRAWABLE_GAME_OBJECT_H
