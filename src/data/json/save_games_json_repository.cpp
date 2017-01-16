//
// Created by robbie on 9-1-2017.
//

#include "save_games_json_repository.h"

namespace data {
    namespace json {

        std::string save_games_json_repository::get_key(std::string &obj) const {
            return obj;
        }

        std::string save_games_json_repository::get_file_location() const {
            return "save_games/saved_games.json";
        }

        std::string *save_games_json_repository::create_from_json(std::string json_string) const {
            try {
                nlohmann::json j = nlohmann::json::parse(json_string);
                std::string file = j["key"];
                return new std::string(file);
            } catch (...) {
                return nullptr;
            }
        }

        std::string save_games_json_repository::to_json(std::string &obj) const {
            nlohmann::json j;
            j["key"] = obj;

            return j.dump();
        }
    }
}
