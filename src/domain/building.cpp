#pragma once
#include "building.h"

namespace domain {
    building::building() {
    }

    int building::getHitPoints() {
        return this->_hitPoints;
    }

    void building::setHitPoints(const int hitPoints) {
        this->_hitPoints = hitPoints;
    }

    int building::getRegenPerSec() {
        this->_regenPerSec;
    }

    void building::setRegenPerSec(const int regenPerSec) {
        this->_regenPerSec = regenPerSec;
    }

    building::~building() {
    }
}