//
// Created by robbie on 15-11-2016.
//

#include "font_manager.h"

namespace engine {
    namespace graphics {

        void font_manager::add(std::string font_file, std::string id) {
            m_fonts[id] = font_file;
        }

        TTF_Font *font_manager::get_font(std::string id, int size) {
            // Check for cached fonts
            std::string cache_key = id + "_" + std::to_string(size);
            if (m_created_fonts.find(cache_key) != m_created_fonts.end()) {
                return m_created_fonts[cache_key];
            }

            // Check if the font file is added
            if (m_fonts.find(id) != m_fonts.end()) {
                auto *font = TTF_OpenFont(m_fonts[id].c_str(), size);
                m_created_fonts[cache_key] = font;
                return font;
            }

            return nullptr;
        }

        font_manager::~font_manager() {
            // Unload created fonts
            for (auto it = m_created_fonts.begin(); it != m_created_fonts.end();) {
                TTF_CloseFont(it->second);
                it = m_created_fonts.erase(it);
            }
        }
    }
}
