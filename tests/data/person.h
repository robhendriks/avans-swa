//
// Created by robbie on 24-10-2016.
//

#ifndef CITY_DEFENCE_PERSON_H
#define CITY_DEFENCE_PERSON_H


/**
 * Test Domain Class
 */
class person {
public:
    person(size_t id, std::string name, size_t age);

    size_t& get_id();
    std::string& get_name();
    size_t& get_age();
private:
    size_t id;
    std::string name;
    size_t age;
};


#endif //CITY_DEFENCE_PERSON_H
