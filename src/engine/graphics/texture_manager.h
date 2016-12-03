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
            texture_manager(SDL_Renderer &r, SDL_Surface &screen_surface);

            ~texture_manager();

            void draw(std::string id, math::box2_t dest) const;

            void draw(SDL_Texture* texture, math::box2_t dest) const;

            void draw(std::string id, math::box2_t src, math::box2_t dest) const;

            void draw(SDL_Texture* texture, math::box2_t src, math::box2_t dest) const;

            void draw(std::string id, math::vec2_t image_start_position, math::box2_t dest) const;

            void draw(SDL_Texture *texture, math::vec2_t image_start_position, math::box2_t dest) const;

            void draw(std::string id, math::vec2_t dest_start_position) const;

            SDL_Texture *find(std::string id) const;

            SDL_Texture* load(SDL_Surface &surface, std::string id);

            SDL_Texture* load(std::string file_name, std::string id);

            SDL_Texture* load_from_svg(std::string file_name, math::box2_t src, float scale, std::string id);

            SDL_Texture* load_text(std::string text, graphics::color4_t color, TTF_Font &font, std::string id);

            math::vec2_t get_size(std::string id) const;

            void unload(std::string id);

        private:
            std::map<std::string, std::tuple<SDL_Texture *, SDL_Surface*>> _texture_map;
            SDL_Renderer &_renderer;
            SDL_Surface &m_screen_surface;
        };
    }
}


#endif //CITY_DEFENCE_TEXTURE_MANAGER_H
