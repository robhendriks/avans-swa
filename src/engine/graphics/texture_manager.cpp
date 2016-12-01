//
// Created by te on 28-Oct-16.
//

#include <SDL_image.h>
#include "texture_manager.h"
#include "box_builder.h"

namespace engine {
    namespace graphics {

        texture_manager::texture_manager(SDL_Renderer &r) : _renderer(r) {
        }

        texture_manager::~texture_manager() {
            // Unload everything
            for (auto it = _texture_map.begin(); it !=_texture_map.end();) {
                unload(it->first);
                it = _texture_map.begin();
            }
        }

        SDL_Texture* texture_manager::load(SDL_Surface *surface, std::string id) {
            if(surface == nullptr)
                return nullptr;

            // Create texture
            SDL_Texture* texture = SDL_CreateTextureFromSurface(&_renderer, surface);

            // Check if the texture is created
            if (texture == nullptr) {
                return texture;
            }

            // Save the texture in the map
            _texture_map[id] = std::make_tuple(texture, surface);

            return texture;
        }

        SDL_Texture* texture_manager::load(std::string file_name, std::string id) {
            SDL_Surface* surface = IMG_Load(file_name.c_str());
            return load(surface, id);
        }

        SDL_Texture* texture_manager::load_text(std::string text, graphics::color4_t color, TTF_Font &font, std::string id) {
            SDL_Surface* text_surface = TTF_RenderText_Blended(&font, text.c_str(), (SDL_Color) color);
            return load(text_surface, id);
        }

        void texture_manager::unload(std::string id) {
            if (_texture_map.find(id) != _texture_map.end()) {
                auto tuple = _texture_map[id];
                SDL_FreeSurface(std::get<1>(tuple));
                SDL_DestroyTexture(std::get<0>(tuple));
                _texture_map.erase(id);
            }
        }

        SDL_Texture * texture_manager::find(std::string id) const {
            if (_texture_map.find(id) != _texture_map.end()) {
                auto tuple = _texture_map.at(id);
                return std::get<0>(tuple);
            }

            return nullptr;
        }

        void texture_manager::draw(SDL_Texture* texture, math::vec2_t image_start_position, math::box2_t dest) const {
            box_builder builder(dest.size());
            builder.as_left_top(image_start_position);

            SDL_Rect sdl_src = (SDL_Rect) builder.build();
            SDL_Rect sdl_dest =(SDL_Rect) dest;

            SDL_RenderCopy(&_renderer, texture, &sdl_src, &sdl_dest);
        }

        void texture_manager::draw(std::string id, math::vec2_t image_start_position, math::box2_t dest) const {
            auto *texture = find(id);
            if (texture != nullptr) {
                draw(texture, image_start_position, dest);
            }
        }

        void texture_manager::draw(std::string id, math::vec2_t dest_start_position) const {
            if (_texture_map.find(id) != _texture_map.end()) {
                auto tuple = _texture_map.at(id);
                int w = std::get<1>(tuple)->w;
                int h = std::get<1>(tuple)->h;
                draw(id, {0, 0}, {dest_start_position, {dest_start_position.x + w, dest_start_position.y + h}});
            }
        }

        math::vec2_t texture_manager::get_size(std::string id) const {
            if (_texture_map.find(id) != _texture_map.end()) {
                auto tuple = _texture_map.at(id);
                return {(float)std::get<1>(tuple)->w, (float)std::get<1>(tuple)->h};
            }

            return {0, 0};
        }
    }
}
