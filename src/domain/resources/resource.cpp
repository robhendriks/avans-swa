#ifndef CITY_DEFENCE_RESOURCE_CPP
#define CITY_DEFENCE_RESOURCE_CPP

#include "resource.h"

namespace domain {
    namespace resources {
        resource::resource() {
        }

        int resource::get_count() {
            return this->_count;
        }

        void resource::set_count(int count) {
            this->_count = count;
        }

        resource_type resource::get_resource_type(){
            return this->_type;
        }

        void resource::set_resource_type(resource_type type) {
            this->_type = type;
        }

        resource::~resource() {
        }

        resource::resource(resource_type _type, int _count) : _type(_type), _count(_count) {}
    }
}
#endif //CITY_DEFENCE_RESOURCE_CPP
