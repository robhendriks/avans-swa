#pragma once
namespace domain {
    enum resource_type
    {
        wood,
        ore,
        gold,
        uranium,
        silicium
    };

    class resource {
    public:
        resource();
        void set_resource_type(resource_type);
        resource_type get_resource_type();
        void set_count(const int count);
        int get_count();
        ~resource();

    private:
        resource_type _type;
        int _count;
    };
}
