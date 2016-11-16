//
// Created by Leendert on 14-11-2016.
//

#include <SDL_log.h>
#include "../../domain/gameworld/game_world.h"
#include "json_map_loader.h"

namespace services {
    namespace level_loader {

        domain::gameworld::game_world json_map_loader::load(std::string file_location) {
            std::ifstream file(file_location);
            if (!file.is_open()) {
                throw std::runtime_error(std::string("Unable to open file: ") + file_location);
            }

            SDL_Log("Loading level: %s\n", "");
            json root;

            try {
                root << file;
            } catch (std::exception &e) {
                // TODO: proper error handling
                throw;
            }

            // create map with tile length and width

            vec2_t result = this->get_length_and_width(root);
            domain::map::map *map = new domain::map::map(result.x, result.y);


            // create tiles
            std::vector<domain::map::base_field *> timeList = this->load_tiles(root, *map);
            std::vector<domain::buildings::building *> objects = load_objects(root, *map);
            //map.add_fields(timeList);


            // create placeable_objects
//            std::vector<domain::map::base_field*> m_fields;
//            std::vector<domain::map::base_field*> _fields_with_object;

            // link placeable_object with the correct tile its placed on.

            // add tiles to map with add_fields() method.

            // add map to game world.

            // return game world
            std::vector<domain::map::base_map*> mapVect;
            mapVect.push_back(map);
            domain::map::map* m = (domain::map::map*) mapVect.at(0);
            auto r = m->get_fields();
            r.size();
            domain::gameworld::game_world res {mapVect};
            return res;
//            std::ifstream file(file_location);
//            if (!file.is_open()) {
//                throw std::runtime_error(std::string("Unable to open file: ") + file_location);
//            }
//
//            SDL_Log("Loading level: %s\n", "");
//            json root;
//
//            try {
//                root << file;
//            } catch (std::exception &e) {
//                // TODO: proper error handling
//                throw;
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


        vec2_t json_map_loader::get_length_and_width(json &root) {
            return {32, 32};
        }

        std::vector<domain::map::base_field *> json_map_loader::load_tiles(json &root, domain::map::map &map) {
            std::vector<domain::map::base_field *> tempTiles;
            if (root.find("tiles") == root.end()) {
                return tempTiles;
            }

            json tiles = root["tiles"];
            if (!tiles.is_object()) {
                return tempTiles;
            }

            size_t tileCount = tiles["count"];
            SDL_Log("Loading %d tile(s)...\n", tileCount);

            json data = tiles["data"];
            if (!data.is_array()) {
                return tempTiles;
            }

            for (json &elem : data) {
                int x = elem["x"];
                int y = elem["y"];
                int type = elem["type"];

                SDL_Log("%d %d %d", x, y, type);

                // TODO: moeten we tiles niet eerst aanmaken?
                //base_field(const std::string &id, const std::string &file_loc, engine::math::vec2_t *image_start_position, int rotation, int x, int y);
                //vec2_t x;
                // maak texture class aan.

                engine::math::vec2_t *v = new engine::math::vec2_t{0, 0};
                auto *field = new domain::map::passable_field("tile", "images/grass.png", v, 0, elem["x"], elem["y"]);

                tempTiles.push_back(field);

//              map_model.tiles.push_back();
            }
            return tempTiles;
            //map.add_fields(tempTiles);
        }

        std::vector<domain::buildings::building *> json_map_loader::load_objects(json root, domain::map::map &map) {
            std::vector<domain::buildings::building *> tempGameObjs;

            if (root.find("objects") == root.end()) {
                return tempGameObjs;
            }

            json level_objects = root["objects"];
            if (!level_objects.is_object()) {
                return tempGameObjs;

            }

            size_t level_objects_count = level_objects["count"];
            SDL_Log("Loading %d level objects(s)...\n", level_objects_count);

            json data = level_objects["data"];
            if (!data.is_array()) {
                return tempGameObjs;
            }

            for (json &elem : data) {
                int x = elem["x"];
                int y = elem["y"];
                int rotation = elem["rotation"];

                SDL_Log("%d %d %d", x, y, rotation);
                // TODO: moeten we gebouw objects niet eerst aanmaken?
                // new level_objects
                // map_model.level_objects.push_back();
                engine::math::vec2_t *v = new engine::math::vec2_t{0, 0};
                //auto *field = new domain::map::passable_field("tile", "images/grass.png", v, 0, elem["x"], elem["y"]);
                auto field = new domain::buildings::building("object", "images/grass.png",v,rotation);
                tempGameObjs.push_back(field);
            }
            return tempGameObjs;
            //map.add_fields(tempGameObjs);
        }

        json_map_loader::~json_map_loader() {

        }

        json_map_loader::json_map_loader() {

        }
    }
}
