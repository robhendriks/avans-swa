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
        bool resource::check_resource(int amount){
            if(_count >=amount){
                return true;
            }else{
                return false;
            }
        }

        void resource::decrement_resource(int amount){
            _count = _count - amount;
        }

        void resource::increment_resource(int amount){
            _count = _count + amount;
        }

        void resource::set_resource_type(resource_type type) {
            this->_type = type;
        }

        resource::~resource() {
        }
    }
}
#endif //CITY_DEFENCE_RESOURCE_CPP
