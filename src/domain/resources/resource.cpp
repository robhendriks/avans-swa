#ifndef CITY_DEFENCE_RESOURCE_CPP
#define CITY_DEFENCE_RESOURCE_CPP

#include "resource.h"

namespace domain {
    namespace resources {
        resource::resource(resource_type type, int count) {
            _type = type;
            _count = count;
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
    }
}
#endif //CITY_DEFENCE_RESOURCE_CPP
