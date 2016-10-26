//
// Created by robbie on 24-10-2016.
//

#ifndef CITY_DEFENCE_PERSON_JSON_REPOSITORY_H
#define CITY_DEFENCE_PERSON_JSON_REPOSITORY_H

#include "../../../src/data/json/json_repository.h"
#include "../person.h"


class person_json_repository : public data::json::json_repository<size_t, person> {
public:
    size_t& get_key(person& obj) const;
    std::string get_file_location()const;
    person* create_from_json(std::string json_string) const;
    std::string to_json(person& obj) const;
};

#endif //CITY_DEFENCE_PERSON_JSON_REPOSITORY_H
