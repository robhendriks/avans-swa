#ifndef CITY_DEFENCE_RESOURCE_CPP
#define CITY_DEFENCE_RESOURCE_CPP

#include "resource.h"

namespace domain {
    namespace resources {

        resource::resource(const std::string &resourcename, int _count) : resourcename(resourcename), _count(_count),
            m_previous_count(-1) {}

        resource::resource() : _count(-1), max_out(false), m_previous_count(-1) {}

        int resource::get_count() const {
            return _count;
        }

        void resource::set_count(int count) {
            _count = count;
        }

        void resource::set_previous_count(int amount) {
            m_previous_count = amount;
        }

        int resource::get_previous_count() const {
            return m_previous_count;
        }

        std::string resource::get_resource_type() const {
            return resourcename;
        }

        bool resource::check_resource(int amount) {
            return _count >= amount;
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
    }
}
#endif //CITY_DEFENCE_RESOURCE_CPP
