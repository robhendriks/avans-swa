#pragma once
#include "resource.h"
namespace domain {
    resource::resource() {
    }

    int resource::getCount() {
        return this->_count;
    }

    void resource::set_count(int count) {
        this->_count = count;
    }

    resource_type resource::get_resource_type(){
        return this->_type;
    }

    void resource::set_resource_type(type) {
        this->_type = type;
    }

    resource::~resource() {
    }
}