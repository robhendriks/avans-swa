#pragma once
#include "building.h"

namespace domain {
    building::building() {
    }

    int building::getHitPoints() {
        return this->_hit_points;
    }

    void building::sethit_points(const int hit_points) {
        this->_hit_points = hit_points;
    }

    int building::get_regen_per_sec() {
        this->_regen_per_sec;
    }

    void building::set_regen_per_sec(const int regen_per_sec) {
        this->_regen_per_sec = regen_per_sec;
    }

    building::~building() {
    }
}