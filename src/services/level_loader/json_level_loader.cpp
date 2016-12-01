//
// Created by robbie on 20-11-2016.
//

#include <fstream>
#include "json_level_loader.h"
#include "../../domain/map/objects/building.h"
#include "../../domain/map/objects/road.h"

namespace services {
    namespace level_loader {

        json_level_loader::json_level_loader(json root) : m_root(root) {

        }


        std::unique_ptr<domain::game_level::game_level> json_level_loader::load() {
            // load nations-url

            std::vector< std::shared_ptr<domain::nations::nation>> avaiable_nations = load_nations(m_root["nations-url"]);

            // load building-url
            std::string building_url = m_root["building-url"];
            std::cout << building_url << std::endl;

            //load levels

            //below needs a new function
            // Create the map
            float width = 16;//m_root["width"];
            float height = 16; //m_root["height"];
            auto map1 = std::shared_ptr<domain::map::map>(new domain::map::map({width - 1, height - 1}, {32, 32}));

            // Load the fields
            load_fields(m_root, *map1);
            // Load the objects
            load_objects(m_root, *map1);

            // Create the level
            auto *d_a_d = new engine::draganddrop::drag_and_drop();
            auto goal = std::make_shared<domain::game_level::game_stats>(domain::game_level::game_stats(3, 0, 10000));

            // this piece is for now placeholder till load_nations work
            auto nation = std::make_shared<domain::nations::nation>(domain::nations::nation("name", "name_pre"));
            std::vector<std::shared_ptr<domain::nations::enemy>> enemies = {};
            enemies.push_back(std::make_shared<domain::nations::enemy>(domain::nations::enemy("name", 1)));
            nation->set_available_enemies(enemies);

            //std::shared_ptr<domain::nations::nation> first_nation = avaiable_nations[0];

            auto game_level = std::unique_ptr<domain::game_level::game_level>(
                new domain::game_level::game_level("level", map1, goal, nation, *d_a_d));

            // TODO: HARDCODED ATM
            // Add placeable objects
            engine::math::box2_t building_box {{0, 0}, {0, 0}}; // This box will be overwritten by the view
            auto *building = new domain::map::objects::building(building_box);
            building->set_draw_settings("images/building-a.png");
            game_level->add_placeable_object(*building);

            // Done with building the level
            return game_level;
        }
      std::vector<std::shared_ptr<domain::nations::nation>> json_level_loader::load_nations(std::string nation_url) {

            //domain nations lijst van enemys
            //domain::nations::enemy
            std::vector<std::shared_ptr<domain::nations::nation>> pre_nation_list;

            std::ifstream file(nation_url);
            if (!file.is_open()) {
                throw std::runtime_error(std::string("Unable to open file: ") + nation_url);
            }

            json nation_root;
            try {
                nation_root << file;

                for (json &elem : nation_root) {

                    //nation.nation(elem["id"],elem["name"]);
                    //TODO: nation maken

                    //<domain::nations::nation::nation> nation = new domain::nations::nation::nation(elem["id"]);
                    pre_nation_list.push_back(std::make_shared<domain::nations::nation>(domain::nations::nation(elem["id"], "_")));
                        //reset(new domain::nations::nation::nation(elem["id"],elem["name"]));
                  // std::shared_ptr<domain::nations::nation> pre_nation= new domain::nations::nation::nation(elem["id"],elem["name"]);
                   // &nation(pre_nation);
//                    std::string id = elem["id"];
//                    std::string name = elem["name"];
                    json data = elem["units"];
                    if (!data.is_array()) {
                        return pre_nation_list;
                    }
//                    std::shared_ptr<domain::nations::enemy>>
                   // std::vector<std::shared_ptr<domain::nations::enemy>> pre_nation;
                    for (json &enemy : data){

//                name": "Fallen Warrior",
//                    "movement-speed": 1,
//                    "min-damage": 3,
//                    "max-damage": 7,
//                    "hitpoints": 120,
//                    "type": "normal",
//                    "oppertunity-cost": 1
                        //current_nation->set_available_enemies()
                        std::string enemy_name = enemy["name"];
                        double enemey_movement_speed = static_cast<double>(enemy["movement-speed"]);
                        int enemey_min_damage = static_cast<int>(enemy["min-damage"]);
                        int enemey_max_damage = static_cast<int>(enemy["max-damage"]);
                        int enemey_hitpoints = static_cast<int>(enemy["hitpoints"]);
                        std::string enemy_type = enemy["type"];
                        int enemey_oppertunity_cost = static_cast<int>(enemy["oppertunity-cost"]);

                        // TODO: create enemy obj en push to list of Nations!

//                        "name": "Fisher",
//                            "movement-speed": 1.6,
//                            "min-damage": 12,
//                            "max-damage": 15,
//                            "hitpoints": 140,
//                            "type": "normal",
//                            "oppertunity-cost": 1
                      //  pre_nation.pushback(new domain::nations::enemy(enemy["name"], enemy["min-damage"],enemy["max-damage"],));

                        std::cout << enemy_name << enemey_min_damage << enemey_max_damage << enemey_hitpoints << enemy_type << enemey_oppertunity_cost << enemey_movement_speed;
                    }
                   // std::cout << id << name;
                }
            } catch (std::exception &e) {
                // TODO: proper error handling
                auto d = e.what();
                std::cout << d ;
                throw;
            }
          return pre_nation_list;
        }

        void json_level_loader::load_fields(json &root, domain::map::map &map1) {
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

                // Create the field, note that the field will automatically be added to the map
                auto *field = new domain::map::field(map1, {(float)x, (float)y});
                field->set_draw_settings("images/grass.png");
            }
        }

        void json_level_loader::load_objects(json &root, domain::map::map &map1) {
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
                return ;
            }

            // Loop through all objects
            for (json &elem : data) {
                std::string id = elem["id"];
                int x = elem["x"];
                int y = elem["y"];
                int rotation = elem["rotation"];

                auto field = map1.get_field({(float)x, (float)y});
                if (field) {
                    domain::map::objects::field_object *object = nullptr;

                    std::string image_location;

                    std::string building_str = "building";
                    if (std::mismatch(building_str.begin(), building_str.end(), id.begin()).first == building_str.end()) {
                        object = new domain::map::objects::building(field);

                        image_location = "images/";
                        image_location += id;
                        image_location += ".png";
                    } else {
                        if (id == "road-straight") {
                            image_location = "images/road-straight.png";
                        } else if (id == "road-junction") {
                            image_location = "images/road-junction.png";
                        } else if (id == "road-corner") {
                            image_location = "images/road-corner.png";
                        } else if (id == "road-t-junction") {
                            image_location = "images/road-t-junction.png";
                        } else {
                            image_location = "images/road-cap.png";
                        }

                        // Create the object
                        object = new domain::map::objects::road(field);
                    }

                    // Calculate the image start position
                    float image_start_y = map1.get_tile_size().y * rotation;

                    // Place the (created) object on the field
                    object->set_draw_settings(image_location, {0, image_start_y});
                    object->set_rotation(rotation);

                    field->place_object(*object);
                }

                SDL_Log("%d %d %d", x, y, rotation);
            }
        }


    }
}
