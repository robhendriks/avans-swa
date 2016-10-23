#pragma once
#include "resource.h"
namespace domain {
    resource::resource() {
    }

    int resource::getCount() {
        return this->_count;
    }

    void resource::setCount(const int count) {
        this->_count = count;
    }

    resource_type resource::getResourceType() {
        return this->_type;
    }

    void resource::setResourceType(type) {
        this->_type = type;
    }

    resource::~resource() {
    }
}