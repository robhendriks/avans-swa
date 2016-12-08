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
            //load_level needs te change in the future
            int load_level_nr = 0;

            std::string nations_filename, buildings_filename;
            nations_filename = m_root.value("nations-url", "nations.json");
            buildings_filename = m_root.value("buildings-url", "buildings.json");

            // Load nations from JSON
            if (m_nations.empty())
                load(nations_filename, m_nations);
            // Load buildings from JSON
            if (m_buildings.empty())
                load(buildings_filename, m_buildings);

            //load lvl src's if not loaded yet
            if (m_maps.empty()) {
                json lvls = m_root["lvls"];
                if (lvls.is_array()) {
                    m_maps.push_back(load_all_levels(lvls[load_level_nr]));
                }
            }

            // Create the level
            auto *d_a_d = new engine::draganddrop::drag_and_drop();
            auto goal = std::make_shared<domain::game_level::game_stats>();
            goal->set_counter("buildings", 5);
            auto game_level = std::unique_ptr<domain::game_level::game_level>(
                new domain::game_level::game_level("level", "", "", m_maps[load_level_nr], goal, m_nations.front(),
                                                   *d_a_d,
                                                   125000));
            for (auto building : m_buildings) {
                game_level->add_placeable_object(*building);
            }

            return game_level;
        }

        void json_level_loader::load_nation_units(nation_ptr &nation, const json &elem) {
            if (elem.find("units") == elem.end()) {
                return;
            }

            json unit_array = elem["units"];
            if (!unit_array.is_array()) {
                return;
            }

            SDL_Log("[%s] Loading %zu unit(s)...\n", nation->get_name().c_str(), unit_array.size());

//                    if (!data.is_array()) {
//                        return pre_nation_list;
//                    }

//                    std::vector<std::shared_ptr<domain::nations::enemy>> pre_vec_enemies;
//                    for (json &enemy : data) {
//                        std::string enemy_name = enemy["name"];
//                        double enemey_movement_speed = static_cast<double>(enemy["movement-speed"]);
//                        int enemey_min_damage = static_cast<int>(enemy["min-damage"]);
//                        int enemey_max_damage = static_cast<int>(enemy["max-damage"]);
//                        int enemey_hitpoints = static_cast<int>(enemy["hitpoints"]);
//                        std::string enemy_type = enemy["type"];
//                        int enemey_oppertunity_cost = static_cast<int>(enemy["oppertunity-cost"]);
//
//                        bool boss = false;
//                        if (enemy_type == "boss") { boss = true; };
//                        //TODO: not 100 dynamic
//                        std::shared_ptr<domain::nations::enemy> curren_enemy =
//                            std::make_shared<domain::nations::enemy>(
//                                domain::nations::enemy(enemy_name, enemey_min_damage, enemey_max_damage, 2,
//                                                       enemey_hitpoints, 100, 2, enemey_movement_speed, boss,
//                                                       current_nation, enemey_oppertunity_cost));
//                        curren_enemy->set_draw_settings("images/building-a.png");
//                        pre_vec_enemies.push_back(curren_enemy);
//                        current_nation->setavailableenemies(pre_vec_enemies);
//                        pre_nation_list.push_back(current_nation);
//                    }
        }

        void json_level_loader::load_fields(json &root, domain::map::map &map1) {
            if (root.find("tiles") == root.end()) {
                return;
            }

            json tile_array = root["tiles"];
            if (!tile_array.is_array()) {
                return;
            }

            SDL_Log("Loading %zu tile(s)...\n", tile_array.size());

            int tileset_columns = 17; // 1088 / 64 = 17

            for (json &elem : tile_array) {
                int tile_x = elem.value("x", -1); // get x, default to -1
                int tile_y = elem.value("y", -1); // get y, default to -1
                int tile_id = elem.value("id", -1); // get id, default to -1
                bool tile_placeable = !elem.value("immutable", false); // get immutability, default to false

                // Report if there's bogus data
                if (tile_x < 0 || tile_y < 0 || tile_id < 0) {
                    throw std::runtime_error("Error: could not load tile");
                }

                // Calculate the tile's sprite row and column
                int image_row = tile_id / tileset_columns;
                int image_column = tile_id % tileset_columns;

                // Create the field and add it to the map
                auto *field = new domain::map::field(map1, {
                    static_cast<float>(tile_x),
                    static_cast<float>(tile_y)});

                auto image_start_position = vec2_t{
                    static_cast<float>(image_column * TILE_WIDTH),
                    static_cast<float>(image_row * TILE_HEIGHT)};

                field->set_draw_settings("images/tileset.png", image_start_position);
            }
        }

        void json_level_loader::load_objects(json &root, domain::map::map &map1) {
            if (root.find("objects") == root.end()) {
                return;
            }

            json object_array = root["objects"];
            if (!object_array.is_array()) {
                return;
            }

            SDL_Log("Loading %zu object(s)...\n", object_array.size());
            return;
            int column = 0;
            // Loop through all objects
            for (json &elem : object_array) {
                std::string id = elem["id"];
                int x = elem["x"];
                int y = elem["y"];
                int rotation = elem["rotation"];

                auto field = map1.get_field({(float) x, (float) y});
                if (field) {
                    domain::map::objects::field_object *object = nullptr;

                    std::string image_location;

                    std::string building_str = "road";
                    if (std::mismatch(building_str.begin(), building_str.end(), id.begin()).first ==
                        building_str.end()) {
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
                        object->set_max_column(1);
                    } else {
                        object = new domain::map::objects::building(field);

                        image_location = "images/";
                        image_location += "building-a";
                        image_location += ".png";
                        object->set_max_column(2);
                    }

                    // Calculate the image start position
                    //TODO: rotation with row
                    float image_start_y = map1.get_tile_size().y * rotation;

                    // Place the (created) object on the field
                    object->set_draw_settings(image_location, {0, image_start_y});
                    object->set_rotation(rotation);

                    object->set_current_column(column);
                    auto b = dynamic_cast<domain::map::objects::building *>(object);
                    if (b != nullptr) {
                        auto m = b->get_health_regen();
                        std::cout << m;
                    }
                    field->place_object(object);
                    column = column + 1 <= object->get_max_column() ? column + 1 : 1;
                }

                SDL_Log("%d %d %d", x, y, rotation);
            }
        }

        building_ptr json_level_loader::load_buildings_json(std::string url) {

        }

        map_ptr json_level_loader::load_all_levels(std::string filename) {
            std::ifstream file;
            file.exceptions(std::ifstream::failbit);

            try {
                file.open(filename);

                json map_root;
                map_root << file;

                int width = map_root.value("width", -1);
                int height = map_root.value("height", -1);

                if (width < 1 || height < 1) {
                    throw std::runtime_error("Error: could not load map");
                }

                // Create the map
                auto map = std::make_shared<domain::map::map>(
                    vec2_t{static_cast<float>(width - 1), static_cast<float>(height - 1)},
                    vec2_t{static_cast<float>(TILE_WIDTH), static_cast<float>(TILE_HEIGHT)});

                load_fields(map_root, *map);
                load_objects(map_root, *map);

                return map;
            } catch (std::exception &e) {
                std::cerr << e.what() << "\n";
                throw;
            }
        }

    }
}
