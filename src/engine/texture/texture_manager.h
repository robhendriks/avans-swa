//
// Created by te on 28-Oct-16.
//

#ifndef CITY_DEFENCE_TEXTURE_MANAGER_H
#define CITY_DEFENCE_TEXTURE_MANAGER_H

#include <string>
#include <map>
#include <SDL.h>

namespace engine {
    namespace texture {
        class texture_manager {
        public:
            texture_manager(SDL_Renderer &r);
            void draw(std::string id, int sourceX, int sourceY, int width, int height, int destX, int destY);
            bool load_texture(std::string file_name, std::string id);
        private:
            std::map<std::string, SDL_Texture*> _texture_map;
            SDL_Renderer &_renderer;
        };
    }
}



#endif //CITY_DEFENCE_TEXTURE_MANAGER_H
