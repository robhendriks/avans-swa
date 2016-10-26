#ifndef CITY_DEFENCE_BUILDING_CPP
#define CITY_DEFENCE_BUILDING_CPP
#include "building.h"

namespace domain {
    building::building() {
    }

    int building::get_hit_points(){
        return this->_hit_points;
    }

    void building::set_hit_points(int hit_points) {
        this->_hit_points = hit_points;
    }

    int building::get_regen_per_sec() {
        return this->_regen_per_sec;
    }

    void building::set_regen_per_sec(int regen_per_sec) {
        this->_regen_per_sec = regen_per_sec;
    }

    building::~building() {
    }
}
#endif //CITY_DEFENCE_BUILDING_CPP
