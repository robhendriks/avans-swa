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
            std::string nations_filename, buildings_filename;
            nations_filename = m_root.value("nations-url", "nations.json");
            buildings_filename = m_root.value("buildings-url", "buildings.json");

            // Load maps from JSON
            // TODO: load levels on demand, not just the first level
            if (m_maps.empty()) {
                json levels = m_root["lvls"];
                if (levels.is_array() && levels.size() > 0) {
                    map_ptr map;
                    load(levels.front(), map);
                    m_maps.push_back(map);
                }
            }

            // Load nations from JSON
            if (m_nations.empty())
                load(nations_filename, m_nations);
            // Load buildings from JSON
            if (m_buildings.empty())
                load(buildings_filename, m_buildings);

            // Create the level
            auto *d_a_d = new engine::draganddrop::drag_and_drop();
            auto goal = std::make_shared<domain::game_level::game_stats>();
            goal->set_counter("buildings", 5);
            auto game_level = std::unique_ptr<domain::game_level::game_level>(
                new domain::game_level::game_level("level", "", "", m_maps.front(), goal, m_nations.front(),
                                                   *d_a_d,
                                                   125000));
            for (auto building : m_buildings) {
                game_level->add_placeable_object(*building);
            }

            return game_level;
        }

    }
}
