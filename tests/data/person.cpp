//
// Created by robbie on 24-10-2016.
//

#include <string>
#include "person.h"

person::person(size_t id, std::string name, size_t age) : id(id), name(name), age(age) {
}

size_t& person::get_id() {
    return id;
}

std::string& person::get_name() {
    return name;
}

size_t& person::get_age() {
    return age;
}
