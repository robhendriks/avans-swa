//
// Created by Leendert on 14-11-2016.
//

#include <SDL_log.h>
#include "json_map_loader.h"
#include "../../config/json_config.h"

namespace services {
    namespace map_loader {

        void json_map_loader::load(const char *filename) {
            std::ifstream file(filename);
            if (!file.is_open()) {
                throw std::runtime_error(std::string("Unable to open file: ") + filename);
            }

            SDL_Log("Loading level: %s\n", filename);
            json root;

            try {
                root << file;
            } catch (std::exception &e) {
                // TODO: proper error handling
                throw;
            }
/*
            size_t width = root["width"];
            size_t height = root["height"];

            // Create map model
            models::main_map_model map_model;
            map_model.map_box = new engine::math::box2_t{0, 0, (float)(width * map_model.tile_width), (float)(height * map_model.tile_height)};

            load_tiles(root, map_model);
            load_objects(root, map_model);
*/
            // TODO:
        }

        void json_map_loader::load_tiles(json &root, models::main_map_model &map_model) {
            if (root.find("tiles") == root.end()) {
                return;
            }

            json tiles = root["tiles"];
            if (!tiles.is_object()) {
                return;
            }

            size_t tileCount = tiles["count"];
            SDL_Log("Loading %d tile(s)...\n", tileCount);

            json data = tiles["data"];
            if (!data.is_array()) {
                return;
            }

            for (json &elem : data) {
                int x = elem["x"];
                int y = elem["y"];
                int type = elem["type"];

                SDL_Log("%d %d %d", x, y, type);
                // TODO: moeten we tiles niet eerst aanmaken?
//                map_model.tiles.push_back();
            }
        }

        void json_map_loader::load_objects(json &root, models::main_map_model &map_model) {
            if (root.find("objects") == root.end()) {
                return;
            }

            json level_objects = root["objects"];
            if (!level_objects.is_object()) {
                return;
            }

            size_t level_objects_count = level_objects["count"];
            SDL_Log("Loading %d level objects(s)...\n", level_objects_count);

            json data = level_objects["data"];
            if (!data.is_array()) {
                return;
            }

            for (json &elem : data) {
                int x = elem["x"];
                int y = elem["y"];
                int rotation = elem["rotation"];

                SDL_Log("%d %d %d", x, y, rotation);
                // TODO: moeten we gebouw objects niet eerst aanmaken?
                // new level_objects
                // map_model.level_objects.push_back();

            }
        }
    }
}
