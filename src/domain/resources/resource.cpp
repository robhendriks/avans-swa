#ifndef CITY_DEFENCE_RESOURCE_CPP
#define CITY_DEFENCE_RESOURCE_CPP

#include "resource.h"

namespace domain {
    namespace resources {
        resource::resource() {
            max_out = false;
        }

        int resource::get_count() {
            return this->_count;
        }

        void resource::set_count(int count) {

            this->_count = count;

        }

        std::string resource::get_resource_type() {
            return resourcename;
        }

        bool resource::check_resource(int amount) {
            if (_count >= amount) {
                return true;
            } else {
                return false;
            }
        }

        void resource::decrement_resource(int amount) {
            if (!max_out) {
                _count = _count - amount;
            }
        }

        void resource::increment_resource(int amount) {

            if (!max_out) {
                _count = _count + amount;
            }

        }

        void resource::set_resource_type(std::string _resourcename) {
            resourcename = _resourcename;
        }

        void resource::max_out_resource() {
            max_out = true;
            _count = 99999;
        }

        resource::~resource() {
        }

        resource::resource(const std::string &resourcename, int _count) : resourcename(resourcename), _count(_count) {}
    }
}
#endif //CITY_DEFENCE_RESOURCE_CPP
