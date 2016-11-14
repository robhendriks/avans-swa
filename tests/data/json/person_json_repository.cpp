//
// Created by robbie on 24-10-2016.
//

#include "person_json_repository.h"
#include "json.hpp"

size_t& person_json_repository::get_key(person& obj) const {
    return obj.get_id();
}

std::string person_json_repository::get_file_location() const {
    return "data/json/persons.json";
}

person* person_json_repository::create_from_json(std::string json_string) const {
    try {
        nlohmann::json j = nlohmann::json::parse(json_string);

        return new person(j["id"], j["name"], j["age"]);
    } catch (...) {
        return nullptr;
    }
}

std::string person_json_repository::to_json(person& obj) const {
    nlohmann::json j;
    j["id"] = obj.get_id();
    j["name"] = obj.get_name();
    j["age"] = obj.get_age();

    return j.dump();
}
