//
// Created by robbie on 15-11-2016.
//

#ifndef CITY_DEFENCE_FONT_MANAGER_H
#define CITY_DEFENCE_FONT_MANAGER_H

#include <string>
#include <map>
#include <SDL_ttf.h>
#include <vector>

namespace engine {
    namespace graphics {
        class font_manager {
        public:
            void add(std::string font_file, std::string id);
            TTF_Font *get_font(std::string id, int size);
            ~font_manager();
        private:
            std::map<std::string, std::string> m_fonts;
            std::map<std::string, TTF_Font*> m_created_fonts;
        };
    }
}

#endif //CITY_DEFENCE_FONT_MANAGER_H
