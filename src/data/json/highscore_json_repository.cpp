//
// Created by robbie on 8-1-2017.
//

#include "highscore_json_repository.h"

namespace data {
    namespace json {

        long highscore_json_repository::get_key(domain::gameworld::highscore &obj) const {
            return obj.get_time();
        }

        std::string highscore_json_repository::get_file_location() const {
            return "highscores.json";
        }

        domain::gameworld::highscore *highscore_json_repository::create_from_json(std::string json_string) const {
            try {
                nlohmann::json j = nlohmann::json::parse(json_string);

                long timestamp = j["time"];
                return new domain::gameworld::highscore(j["score"], timestamp);
            } catch (...) {
                return nullptr;
            }
        }

        std::string highscore_json_repository::to_json(domain::gameworld::highscore &obj) const {
            nlohmann::json j;
            j["score"] = obj.get_score();
            j["time"] = obj.get_time();

            return j.dump();
        }
    }
}
