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
        void setResourceType(resource_type);
        resource_type getResourceType();
        void setCount(const int count);
        int getCount();
        ~resource();

    private:
        resource_type _type;
        int _count;
    };
}
