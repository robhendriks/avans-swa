#ifndef CITY_DEFENCE_RESOURCE_H
#define CITY_DEFENCE_RESOURCE_H

#include <string>
namespace domain {
    namespace resources {


        class resource {
        public:
            resource();

            resource(const std::string &resourcename, int _count);

            void set_resource_type(std::string _resourcename);

            std::string get_resource_type();

            void set_count(int count);

            int get_count();

            //Check if amount of resources exceeds the required amount.
            //Returns False when amount is higher than count; else true
            bool check_resource(int amount);

            //Decrement the resource with the given amount. Only use after you used check_resource!!
            void decrement_resource(int amount);

            //Increment the resource with the given amount.
            void increment_resource(int amount);

            ~resource();

        private:
            std::string resourcename;
            int _count;
        };
    }
}
#endif //CITY_DEFENCE_RESOURCE_H
