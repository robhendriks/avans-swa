//
// Created by te on 28-Oct-16.
//

#include <SDL_image.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define NANOSVG_IMPLEMENTATION

#include "nanosvg.h"

#define NANOSVGRAST_IMPLEMENTATION

#include "nanosvgrast.h"
#include "texture_manager.h"
#include "box_builder.h"

namespace engine {
    namespace graphics {

        texture_manager::texture_manager(SDL_Renderer &r, SDL_Surface &screen_surface) : _renderer(r),
                                                                                         m_screen_surface(
                                                                                             screen_surface) {
        }

        texture_manager::~texture_manager() {
            // Unload everything
            for (auto it = _texture_map.begin(); it != _texture_map.end();) {
                unload(it->first);
                it = _texture_map.begin();
            }
        }

        SDL_Texture *texture_manager::load(SDL_Surface &surface, std::string id) {
            // Create texture
            SDL_Texture *texture = SDL_CreateTextureFromSurface(&_renderer, &surface);

            // Check if the texture is created
            if (texture == nullptr) {
                return texture;
            }

            // Make sure it is unloaded when something is already loaded with the same id
            //unload(id);

            // Save the texture in the map
            _texture_map[id] = std::make_tuple(texture, &surface);

            return texture;
        }

        SDL_Texture *texture_manager::load(std::string file_name, std::string id) {
            SDL_Surface *surface = IMG_Load(file_name.c_str());
            return load(*surface, id);
        }

        SDL_Texture *
        texture_manager::load_text(std::string text, graphics::color4_t color, TTF_Font &font, std::string id) {
            SDL_Surface *text_surface = TTF_RenderText_Blended(&font, text.c_str(), (SDL_Color) color);
            return load(*text_surface, id);
        }

        SDL_Texture *
        texture_manager::load_text(std::string text, graphics::color4_t color, TTF_Font &font, std::string id, int pixels) {
            SDL_Surface *text_surface = TTF_RenderText_Blended_Wrapped(&font, text.c_str(), (SDL_Color) color, pixels);
            return load(*text_surface, id);
        }

        void texture_manager::unload(std::string id) {
            if (_texture_map.find(id) != _texture_map.end()) {
                auto tuple = _texture_map[id];
                SDL_FreeSurface(std::get<1>(tuple));
                SDL_DestroyTexture(std::get<0>(tuple));
                _texture_map.erase(id);
            }
        }

        SDL_Texture *texture_manager::find(std::string id) const {
            if (_texture_map.find(id) != _texture_map.end()) {
                auto tuple = _texture_map.at(id);
                return std::get<0>(tuple);
            }

            return nullptr;
        }

        void texture_manager::draw(std::string id, math::box2_t dest) const {
            auto *texture = find(id);
            if (texture != nullptr) {
                draw(texture, dest);
            }
        }

        void texture_manager::draw(SDL_Texture *texture, math::box2_t dest) const {
            SDL_Rect sdl_dest = (SDL_Rect) dest;
            SDL_RenderCopy(&_renderer, texture, NULL, &sdl_dest);
        }

        void texture_manager::draw(std::string id, math::box2_t src, math::box2_t dest) const {
            auto *texture = find(id);
            if (texture != nullptr) {
                draw(texture, src, dest);
            }
        }

        void texture_manager::draw(SDL_Texture *texture, math::box2_t src, math::box2_t dest) const {
            SDL_Rect sdl_src = (SDL_Rect) src;
            SDL_Rect sdl_dest = (SDL_Rect) dest;

            SDL_RenderCopy(&_renderer, texture, &sdl_src, &sdl_dest);
        }

        void texture_manager::draw(SDL_Texture *texture, math::vec2_t image_start_position, math::box2_t dest) const {
            box_builder builder(dest.size());
            builder.as_left_top(image_start_position);

            draw(texture, builder.build(), dest);
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
                return {(float) std::get<1>(tuple)->w, (float) std::get<1>(tuple)->h};
            }

            return {0, 0};
        }

        SDL_Texture *
        texture_manager::load_from_svg(std::string file_name, math::box2_t src, float scale, std::string id) {
            //using nanosvg
            NSVGimage *image = NULL;
            NSVGrasterizer *rast = NULL;
            unsigned char *img = NULL;

            const char *filename = file_name.c_str();

            image = nsvgParseFromFile(filename, "px", 96.0f);
            if (image == NULL) {
                printf("Could not open SVG image.\n");
                return nullptr;
            }

            //Get image dimensions
            //int image_width = static_cast<int>(image->width);
            //int image_height = static_cast<int>(image->height);
            int width = static_cast<int>(src.width());
            int height = static_cast<int>(src.height());
            int width_with_scale = static_cast<int>(width * scale);
            int height_with_scale = static_cast<int>(height * scale);


            rast = nsvgCreateRasterizer();
            if (rast == NULL) {
                printf("Could not init rasterizer.\n");

                nsvgDelete(image);
                return nullptr;
            }

            img = (unsigned char *) malloc(width_with_scale * height_with_scale * 4);
            if (img == NULL) {
                printf("Could not alloc image buffer.\n");

                nsvgDelete(image);
                nsvgDeleteRasterizer(rast);
                return nullptr;
            }

            nsvgRasterize(rast, image, -(src.min.x * scale), -(src.min.y * scale), scale, img, width_with_scale, height_with_scale, width_with_scale * 4);

            auto *surface = SDL_CreateRGBSurfaceFrom(img, //pointer to the pixels
                                                     width_with_scale, //Width
                                                     height_with_scale, //Height
                                                     32, //Depth (bits per pixel)
                                                     width_with_scale * 4, //Pitch (width*depth_in_bytes, in this case)
                                                     0x000000FF, //Red mask
                                                     0x0000FF00, //Green mask
                                                     0x00FF0000, //Blue mask
                                                     0xFF000000); //Alpha mask (alpha in this format)

            nsvgDelete(image);
            nsvgDeleteRasterizer(rast);

            return load(*surface, id);
        }
    }
}
