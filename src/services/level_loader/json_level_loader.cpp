//
// Created by robbie on 20-11-2016.
//

#include <fstream>
#include "json_level_loader.h"
#include "../../domain/map/objects/road.h"

#include "../../domain/map/objects/defensive_building.h"
#include "../../domain/map/objects/economic_building.h"

namespace services {
    namespace level_loader {

        json_level_loader::json_level_loader(json root) : m_root(root) {

        }


        std::unique_ptr<domain::game_level::game_level> json_level_loader::load(int id) {
            //load_level needs te change in the future
            id = 0;

            //load nations if not loaded yet.
            if (this->vec_nations.empty()) {
                vec_nations = load_nations(
                    m_root["nations-url"]);
            }

            //load buildings if not loaded yet
            if (this->vec_building.empty()) {
                std::string buildings = m_root["building-url"];
                load_buildings(buildings);
            }
            if (this->vec_building.empty()) {
                json buildings = m_root["buildings"];
                if (buildings.is_array()) {
                    for (json &building : buildings) {
                        vec_building.push_back(load_buildings(building));
                    }
                }
            }

            //load lvl src's if not loaded yet
            if(vec_levels.empty()){
                json lvls = m_root["lvls"];
                if (lvls.is_array()) {
                    vec_levels.push_back(load_all_levels(lvls[0]));
                }
            }

            // Create the level
            auto *d_a_d = new engine::draganddrop::drag_and_drop();
            auto goal = std::make_shared<domain::game_level::game_stats>(domain::game_level::game_stats());
            goal->set_counter("buildings", 5);
            auto game_level = std::unique_ptr<domain::game_level::game_level>(
                new domain::game_level::game_level("level", vec_levels[0], goal, vec_nations.front(),
                                                   *d_a_d,
                                                   125000));
            for (auto building : vec_building) {
                game_level->add_placeable_object(*building);
            }

            return game_level;
        }


        std::vector<std::shared_ptr<domain::nations::nation>>
        json_level_loader::load_nations(std::string nation_url) {

            std::vector<std::shared_ptr<domain::nations::nation>> pre_nation_list;

            std::ifstream file(nation_url);
            if (!file.is_open()) {
                throw std::runtime_error(std::string("Unable to open file: ") + nation_url);
            }

            json nation_root;
            try {
                nation_root << file;

                for (json &elem : nation_root) {
                    auto current_nation = std::make_shared<domain::nations::nation>(
                        domain::nations::nation(elem["id"], "_"));

                    json data = elem["units"];
                    if (!data.is_array()) {
                        return pre_nation_list;
                    }
                    std::vector<std::shared_ptr<domain::nations::enemy>> pre_vec_enemies;
                    for (json &enemy : data) {
                        std::string enemy_name = enemy["name"];
                        double enemey_movement_speed = static_cast<double>(enemy["movement-speed"]);
                        int enemey_min_damage = static_cast<int>(enemy["min-damage"]);
                        int enemey_max_damage = static_cast<int>(enemy["max-damage"]);
                        int enemey_hitpoints = static_cast<int>(enemy["hitpoints"]);
                        std::string enemy_type = enemy["type"];
                        int enemey_oppertunity_cost = static_cast<int>(enemy["oppertunity-cost"]);


                        bool boss = false;
                        if (enemy_type == "boss") { boss = true; };
                        //TODO: not 100 dynamic
                        std::shared_ptr<domain::nations::enemy> curren_enemy =
                            std::make_shared<domain::nations::enemy>(
                                domain::nations::enemy(enemy_name, enemey_min_damage, enemey_max_damage, 2,
                                                       enemey_hitpoints, 100, 2, enemey_movement_speed, boss,
                                                       current_nation, enemey_oppertunity_cost));
                        curren_enemy->set_draw_settings("images/Fisher.png");
                        curren_enemy->set_max_row(8);
                        curren_enemy->set_max_column(3);
                        pre_vec_enemies.push_back(curren_enemy);
                        current_nation->set_available_enemies(pre_vec_enemies);
                        pre_nation_list.push_back(current_nation);
                    }

                }
            } catch (std::exception &e) {
                // TODO: proper error handling
                auto d = e.what();
                std::cout << d;
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
                auto *field = new domain::map::field(map1, {(float) x, (float) y});
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
                return;
            }

            int column = 0;
            // Loop through all objects
            for (json &elem : data) {
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
                    field->place_object(object);
                    column = column + 1 <= object->get_max_column() ? column + 1 : 1;
                }

                SDL_Log("%d %d %d", x, y, rotation);
            }
        }

        std::shared_ptr<domain::map::objects::building> json_level_loader::load_buildings(std::string url) {
            std::shared_ptr<domain::map::objects::building> building;
            std::ifstream file(url);
            if (!file.is_open()) {
                throw std::runtime_error(std::string("Unable to open file: ") + url);
            }

            json building_root;
            try {
                building_root << file;

                for (json &building_data : building_root) {

                    int min_dmg = 0;
                    int max_dmg = 0;
                    int range = 0;
                    int type = building_data["type"];
                    auto output_sources = std::shared_ptr<domain::resources::resource>();
                    auto costs = std::vector<std::shared_ptr<domain::resources::resource>>();
                    engine::math::box2_t building_box{{10, 10},
                                                      {42, 42}};

                    auto data_building_cost = building_data["cost"];
                    auto it = data_building_cost.begin();
                    for (json::iterator building_costs_item = data_building_cost.begin();
                         it != data_building_cost.end(); ++it) {

                        costs.push_back(std::make_shared<domain::resources::resource>(building_costs_item.key(),
                                                                                      building_costs_item.value()));
                    }


                    for (json &building_properties : building_data["properties"]) {

                        auto current_prop = building_properties.begin();
                        for (json::iterator building_property_item = building_properties.begin();
                             current_prop != building_properties.end(); ++current_prop) {
                            //type 2 = dmg building

                            if (type == 2) {
                                if (building_property_item.key() == "min-damage") {
                                    min_dmg = static_cast<int>(building_property_item.value());
                                } else if (building_property_item.key() == "max-damage") {
                                    max_dmg = static_cast<int>(building_property_item.value());
                                } else if (building_property_item.key() == "range") {
                                    range = static_cast<int>(building_property_item.value());
                                }


                            } else {

                                output_sources = std::make_shared<domain::resources::resource>(
                                    building_property_item.key(),
                                    building_property_item.value());

                            }

                        }
                    }
                    if (type == 1) {
                        std::shared_ptr<domain::map::objects::economic_building> economic_building = std::make_shared<domain::map::objects::economic_building>(
                            building_box,
                            building_data["id"],
                            static_cast<int>(building_data["hitpoints"]),
                            static_cast<double>(building_data["health-regen"]),
                            building_data["name"],
                            costs, output_sources);
                        economic_building->set_draw_settings("images/building-a.png");
                        vec_building.push_back(economic_building);
                    } else {
                        std::shared_ptr<domain::map::objects::defensive_building> defencive_building = std::make_shared<domain::map::objects::defensive_building>(
                            building_box,
                            building_data["id"],
                            static_cast<int>(building_data["hitpoints"]),
                            static_cast<double>(building_data["health-regen"]),
                            building_data["name"],
                            costs, min_dmg, max_dmg, range);
                        defencive_building->set_draw_settings("images/building-a.png");
                        vec_building.push_back(defencive_building);
                    }


                }
            } catch (std::exception &e) {
                // TODO: proper error handling
                auto d = e.what();
                std::cout << d;
                throw;
            }
            return building;
        }

        std::shared_ptr<domain::map::map> json_level_loader::load_all_levels(std::string url) {

            std::shared_ptr<domain::map::map> map;
            std::ifstream file(url);
            if (!file.is_open()) {
                throw std::runtime_error(std::string("Unable to open file: ") + url);

            }

            json map_root;
            try {
                map_root << file;

                float width = map_root["width"];
                float height = map_root["height"];
                map = std::shared_ptr<domain::map::map>(new domain::map::map({width - 1, height - 1}, {32, 32}));
                load_fields(map_root, *map);
                load_objects(map_root, *map);
            } catch (std::exception &e) {
                // TODO: proper error handling
                auto d = e.what();
                std::cout << d;
                throw;
            }
            return map;
        }

        int json_level_loader::get_level_count() {
            if(vec_levels.empty()){
                json lvls = m_root["lvls"];
            }

            return vec_levels.size();
        }

    }
}
