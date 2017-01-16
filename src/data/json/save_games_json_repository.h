//
// Created by robbie on 9-1-2017.
//

#ifndef CITY_DEFENCE_SAVE_GAMES_JSON_REPOSITORY_H
#define CITY_DEFENCE_SAVE_GAMES_JSON_REPOSITORY_H

#include "json_repository.h"

namespace data {
    namespace json {
        class save_games_json_repository : public data::json::json_repository<std::string, std::string> {
        public:
            std::string get_key(std::string &obj) const;

            std::string get_file_location() const;

            std::string *create_from_json(std::string json_string) const;

            std::string to_json(std::string &obj) const;
        };
    }
}


#endif //CITY_DEFENCE_SAVE_GAMES_JSON_REPOSITORY_H
