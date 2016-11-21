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
            std::vector<domain::map::base_field *> tile_list = this->load_tiles(root);
            std::vector<building_objects_with_pos *> game_object_list = load_buildings(root);
            std::vector<road_objects_with_pos *> road_objects_list = load_roads(root);
            int game_obj_counter = 0;
            int road_object_counter = 0;
            int tile_count = 0;
            for (auto &tile : tile_list) // access by reference to avoid copying
            {
                tile_count++;
                //Check if object is on the same place as tile.
                while ((int) game_object_list.size() != game_obj_counter) {
                    int tilePosx = tile->get_x();
                    if(tilePosx == 7){
                        std::cout<<"hoi";
                    }
                    if (tile->get_x() == game_object_list.at(game_obj_counter)->X &&
                        tile->get_y() == game_object_list.at(game_obj_counter)->Y) {
                        tile->place(game_object_list.at(game_obj_counter)->object);
                        game_obj_counter++;
                    } else {
                        game_obj_counter++;
                    }
                }
                while ((int) road_objects_list.size() != road_object_counter) {
                    if (tile->get_x() == road_objects_list.at(road_object_counter)->X &&
                        tile->get_y() == road_objects_list.at(road_object_counter)->Y) {
                        tile->place(road_objects_list.at(road_object_counter)->object);
                        road_object_counter++;
                    } else {
                        road_object_counter++;
                    }
                }
                road_object_counter = 0;
                game_obj_counter = 0;
            }
            //map.add_fields(tile_list);
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
             auto b = tile_list.at(21)->get_placed_object();
            //21 / 22/ 23 /24
#pragma GCC diagnostic pop

            map->add_fields(tile_list);

            std::vector<std::shared_ptr<domain::map::base_map>> mapVect;
            mapVect.push_back(std::shared_ptr<domain::map::base_map>(map));
            std::shared_ptr<domain::map::base_map> m = (std::shared_ptr<domain::map::base_map>) mapVect.at(0);
            auto r = m->get_fields();
            r.size();
            domain::gameworld::game_world res = domain::gameworld::game_world(mapVect);
            return res;
        }

        vec2_t json_map_loader::get_length_and_width(json &root) {
            return {32, 32};
        }

        std::vector<domain::map::base_field *> json_map_loader::load_tiles(json &root) {
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

                engine::math::vec2_t *v = new engine::math::vec2_t{0, 0};
                auto *field = new domain::map::passable_field("tile", "images/grass.png", v, elem["x"], elem["y"]);

                tempTiles.push_back(field);
            }
            return tempTiles;
            //map.add_fields(tempTiles);
        }

        std::vector<json_map_loader::building_objects_with_pos *> json_map_loader::load_buildings(json &root) {
            std::vector<building_objects_with_pos *> temp_game_objs;
            json_map_loader::building_objects_with_pos *game_object = new json_map_loader::building_objects_with_pos();

            if (root.find("objects") == root.end()) {
                temp_game_objs.push_back(game_object);
                //return temp_game_objs;
            }

            json level_objects = root["objects"];
            if (!level_objects.is_object()) {
                //return nullptr;

            }

            size_t level_objects_count = level_objects["count"];
            SDL_Log("Loading %d level objects(s)...\n", level_objects_count);

            json data = level_objects["data"];
            if (!data.is_array()) {
                //return nullptr;
            }
            std::string item_name = "building";
            for (json &elem : data) {
                std::string id = elem["id"];
                int x = elem["x"];
                int y = elem["y"];
                int rotation = elem["rotation"];

                //std::size_t found = id.find_first_of(item_name);
                auto res = std::mismatch(item_name.begin(), item_name.end(), id.begin());
                if (res.first == item_name.end()) {

                    SDL_Log("%d %d %d", x, y, rotation);
                    // TODO: moeten we gebouw objects niet eerst aanmaken?
                    // new level_objects
                    // map_model.level_objects.push_back();
                    engine::math::vec2_t *v = new engine::math::vec2_t{0, 0};
                    //auto *field = new domain::map::passable_field("tile", "images/grass.png", v, 0, elem["x"], elem["y"]);


                    game_object->object = new domain::buildings::building("building", "images/building.png", v, rotation);
                    game_object->X = x;
                    game_object->Y = y;
                    temp_game_objs.push_back(game_object);
                }
            }
            return temp_game_objs;
            //map.add_fields(temp_game_objs);
        }

        std::vector<json_map_loader::road_objects_with_pos *> json_map_loader::load_roads(json &root) {
            std::vector<road_objects_with_pos *> temp_game_objs;

            if (root.find("objects") == root.end()) {
                //return temp_game_objs;
            }

            json level_objects = root["objects"];
            if (!level_objects.is_object()) {
                //return nullptr;
            }

            size_t level_objects_count = level_objects["count"];
            SDL_Log("Loading %d level objects(s)...\n", level_objects_count);

            json data = level_objects["data"];
            if (!data.is_array()) {
                //return nullptr;
            }
            std::string item_name = "road";
            for (json &elem : data) {
                std::string id = elem["id"];
                int rotation = elem["rotation"];
                auto res = std::mismatch(item_name.begin(), item_name.end(), id.begin());
                if (res.first == item_name.end()) {
                    //SDL_Log("%d %d %d", x, y, rotation);
                    // TODO: moeten we gebouw objects niet eerst aanmaken?
                    // new level_objects
                    // map_model.level_objects.push_back();
                    engine::math::vec2_t *v = new engine::math::vec2_t{0, static_cast<float>(rotation)};

                    std::string image_url_for_road = "images/";
                    image_url_for_road += elem["id"];
                    image_url_for_road += ".png";
                    json_map_loader::road_objects_with_pos *game_object = new json_map_loader::road_objects_with_pos();

//
                    game_object->X = elem["x"];
                    game_object->Y = elem["y"];
                    game_object->object = new domain::buildings::building("roads", image_url_for_road, v, rotation);
                    temp_game_objs.push_back(game_object);
                }
            }
            return temp_game_objs;
            //map.add_fields(temp_game_objs);
        }

        json_map_loader::~json_map_loader() {

        }

        json_map_loader::json_map_loader() {

        }
    }
}
