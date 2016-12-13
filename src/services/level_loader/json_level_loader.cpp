//
// Created by robbie on 20-11-2016.
//

#include "json_level_loader.h"

namespace services {
    namespace level_loader {

        const int json_level_loader::TILE_WIDTH = 64;
        const int json_level_loader::TILE_HEIGHT = 64;

        json_level_loader::json_level_loader(json root)
            : m_root(root) {}

        template<typename T>
        bool json_level_loader::load(const std::string &filename, T &obj) {
            try {
                obj = json_deserialize_file<T>(filename);
                return true;
            } catch (const std::exception &e) {
                std::cerr << "Exception: " << e.what() << "\n";
                return false;
            }
        }

        std::unique_ptr<domain::game_level::game_level> json_level_loader::load() {
            int level_idx = 0;
            int nation_idx = 0;

            std::string nations_filename, buildings_filename;
            nations_filename = m_root.value("nations-url", "nations.json");
            buildings_filename = m_root.value("buildings-url", "buildings.json");

            // Load maps from JSON
            if (m_maps.empty()) {
                json levels = m_root["lvls"];
                if (levels.is_array() && levels.size() > 0) {
                    m_maps.push_back(load_map(levels[level_idx]));
                }
            }

            // Load nations from JSON
            if (m_nations.empty())
                load(nations_filename, m_nations);

            // Load buildings from JSON
            if (m_buildings.empty())
                load(buildings_filename, m_buildings);

            // Create drag n' drop
            auto *dnd = new engine::draganddrop::drag_and_drop();

            // Create stats
            auto &meta = m_maps[level_idx]->get_meta();
            auto stats = std::make_shared<domain::game_level::game_stats>();

            // Set goals
            for (auto &it : meta->goals)
                stats->set_counter(it.first, it.second);

            auto game_level = std::make_unique<domain::game_level::game_level>(meta->id, meta->title, meta->description,
                                                                               m_maps[level_idx], stats,
                                                                               m_nations[nation_idx], *dnd,
                                                                               meta->duration);

            for (auto building : m_buildings)
                game_level->add_placeable_object(*building);

            return game_level;
        }

        map_ptr json_level_loader::load_map(const std::string &filename) {
            // for the time being

            std::ifstream file;
//            file.exceptions(std::ifstream::failbit);

            try {
                file.open(filename);
                nlohmann::json json;
                json << file;

                auto deserializer = std::make_unique<map_deserializer>();
                return deserializer->deserialize(json);
            } catch (const std::exception &e) {
                SDL_Log("Unable to load map: %s\n", e.what());
            }
            return nullptr;
        }

    }
}
