//
// Created by robbie on 8-1-2017.
//

#include "json_world_saver.h"
#include "../../utils/string_utils.h"
#include "../../domain/map/objects/road.h"
#include <fstream>

namespace services {
    namespace world_saver {

        json_world_saver::json_world_saver(data::json::save_games_json_repository &save_games_json_repository) :
            m_save_games_json_repository(save_games_json_repository) {

        }

        void json_world_saver::save(domain::gameworld::game_world &world) {
            // Create a unique filename
            char buff[20];
            time_t t = time(0);
            strftime(buff, 15, "%Y%m%d%H%M%S", std::localtime(&t));
            std::string id = buff;

            std::ofstream file;

            // The scenario json
            nlohmann::json j = {{"nations-url", "nations.json"},
                                {"building-url", "buildings.json"},
                                {"lvls", {}},
                                {"start_level", 1}
            };

            // Create the level files
            std::vector<std::string> filenames;
            int counter = 1;
            for (auto &level : world.get_levels()) {
                std::string filename = "level_" + std::to_string(counter) + "_" + id;

                // Open the file
                filename = "save_games/" + filename + ".json";
                file.open (filename);

                // Write to the file
                file << level_to_json(*level).dump();

                // Close the file
                file.close();

                filenames.push_back(filename);
                j["lvls"].push_back(filename);

                // Set start level
                if (world.get_current_level() == level) {
                    if (level->get_state() == domain::game_level::TRANSITION) {
                        j["start_level"] = counter + 1;
                    } else {
                        j["start_level"] = counter;
                    }
                }

                counter++;
            }

            // Create the scenarios file
            std::string scenario_filename = "save_games/scenarios_" + id + ".json";
            file.open (scenario_filename);

            file << j.dump();

            file.close();

            // Save in saved_games file
            m_save_games_json_repository.load();
            m_save_games_json_repository.save(scenario_filename);
            m_save_games_json_repository.commit();
        }

        nlohmann::json json_world_saver::level_to_json(domain::game_level::game_level &level) {
            nlohmann::json j = {
                {"width", level.get_map().get_size().x + 1},
                {"height", level.get_map().get_size().y + 1},
                {"time", level.get_max_duration()},
                {"goals", {}},
                {"resources", {}},
                {"tiles", {{"count", 0}, {"data", {}}}},
                {"objects", {{"count", 0}, {"data", {}}}}
            };

            // Set played time
            if (level.get_state() == domain::game_level::DONE || level.get_state() == domain::game_level::TRANSITION) {
                j["played_time"] = level.get_duration();
            } else if (level.get_state() == domain::game_level::PLAYING) {
                j["played_time"] = level.get_played_time();
            }

            // Add the goals
            for (auto &goal : level.get_goal().get()) {
                j["goals"].push_back({{"type", goal.first}, {"number", goal.second}});
            }

            // Add the resources
            for (auto &resource : level.get_resources()) {
                j["resources"].push_back({{"type", resource->get_resource_type()}, {"amount", resource->get_count()}});
            }

            // Add the tiles
            int tiles_count = 0;
            int objects_count = 0;
            for (auto &field : level.get_map().get_fields()) {
                if (field) {
                    j["tiles"]["data"].push_back({{"type", 4}, {"x", field->get_position().x},
                                                  {"y", field->get_position().y}});
                    tiles_count++;

                    if (field->has_object()) {
                        std::string id = "";
                        auto *building = dynamic_cast<domain::map::objects::building*>(field->get_object());
                        if (building) {
                            id = building->get_id();
                        } else {
                            auto *road = dynamic_cast<domain::map::objects::road*>(field->get_object());
                            if (road) {
                                id = road->get_type();
                            }
                        }

                        j["objects"]["data"].push_back({{"id", id},
                                                        {"x", field->get_position().x},
                                                        {"y", field->get_position().y},
                                                        {"rotation", field->get_object()->get_rotation()}});
                        objects_count++;
                    }
                }
            }

            // Set counts
            j["tiles"]["count"] = tiles_count;
            j["objects"]["count"] = objects_count;

            return j;
        }
    }
}
