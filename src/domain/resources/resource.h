#ifndef CITY_DEFENCE_RESOURCE_H
#define CITY_DEFENCE_RESOURCE_H

namespace domain {
    namespace resources {
        enum resource_type {
            wood,
            ore,
            gold,
            uranium,
            silicium
        };

        class resource {
        public:
            resource();

            resource(resource_type _type, int _count);

            void set_resource_type(resource_type);

            resource_type get_resource_type();

            void set_count(int count);

            int get_count();

            ~resource();

        private:
            resource_type _type;
            int _count;
        };
    }
}
#endif //CITY_DEFENCE_RESOURCE_H
