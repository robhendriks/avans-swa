//
// Created by te on 28-Oct-16.
//

#ifndef CITY_DEFENCE_TEXTURE_MANAGER_H
#define CITY_DEFENCE_TEXTURE_MANAGER_H

#include <string>
#include <map>
#include <SDL.h>
#include <tuple>
#include <SDL_ttf.h>
#include "../math/vec2.hpp"
#include "../math/box2.hpp"
#include "color4.hpp"
#include <memory>

namespace engine {
    namespace graphics {
        class texture_manager {
        public:
            texture_manager(SDL_Renderer &r);

            ~texture_manager();

            void draw(std::string id, math::vec2_t image_start_position, math::box2_t dest) const;

            void draw(SDL_Texture *texture, math::vec2_t image_start_position, math::box2_t dest) const;

            void draw(std::string id, math::vec2_t dest_start_position) const;

            SDL_Texture *find(std::string id) const;

            bool load(SDL_Surface *surface, std::string id);

            bool load(std::string file_name, std::string id);

            bool load_text(std::string text, graphics::color4_t color, TTF_Font &font, std::string id);

            int get_width(std::string id) const;

            int get_height(std::string id) const;

            void unload(std::string id);

        private:
            std::map<std::string, std::tuple<SDL_Texture *, SDL_Surface*>> _texture_map;
            SDL_Renderer &_renderer;
        };
    }
}


#endif //CITY_DEFENCE_TEXTURE_MANAGER_H
