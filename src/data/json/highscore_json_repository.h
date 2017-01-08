//
// Created by robbie on 8-1-2017.
//

#ifndef CITY_DEFENCE_HIGHSCORE_JSON_REPOSITORY_H
#define CITY_DEFENCE_HIGHSCORE_JSON_REPOSITORY_H

#include <cstddef>
#include "../../domain/gameworld/highscore.h"
#include "json_repository.h"

namespace data {
    namespace json {
        class highscore_json_repository : public data::json::json_repository<long, domain::gameworld::highscore> {
        public:
            long get_key(domain::gameworld::highscore &obj) const;

            std::string get_file_location() const;

            domain::gameworld::highscore *create_from_json(std::string json_string) const;

            std::string to_json(domain::gameworld::highscore &obj) const;
        };
    }
}


#endif //CITY_DEFENCE_HIGHSCORE_JSON_REPOSITORY_H
