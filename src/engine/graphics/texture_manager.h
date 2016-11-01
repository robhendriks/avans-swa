//
// Created by te on 28-Oct-16.
//

#ifndef CITY_DEFENCE_TEXTURE_MANAGER_H
#define CITY_DEFENCE_TEXTURE_MANAGER_H

#include <string>
#include <map>
#include <SDL.h>
#include "../math/vec2.hpp"
#include "../math/box2.hpp"

namespace engine {
    namespace graphics {
        class texture_manager {
        public:
            texture_manager(SDL_Renderer &r);
            void draw(std::string id, math::vec2_t image_start_position, math::box2_t dest);
            bool load(std::string file_name, std::string id);
            void unload(std::string id);
        private:
            std::map<std::string, SDL_Texture*> _texture_map;
            SDL_Renderer &_renderer;
        };
    }
}



#endif //CITY_DEFENCE_TEXTURE_MANAGER_H
