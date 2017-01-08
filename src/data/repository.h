//
// Created by robbie on 24-10-2016.
//

#ifndef CITY_DEFENCE_REPOSITORY_H
#define CITY_DEFENCE_REPOSITORY_H

#include <vector>
#include <cstddef>

namespace data {
    template<typename K, typename V>
    class repository {
    public:
        virtual void save(V& obj) = 0;
        virtual void remove(V& obj) = 0;
        virtual V* get_by_key(K key) const = 0;
        virtual std::vector<V*> all() const = 0;
        virtual size_t size() const = 0;
        virtual void commit() = 0;
        virtual void rollback() = 0;

        void operator<<(V& obj) {
            save(obj);
        }

        void operator>>(V& obj) {
            remove(obj);
        }

        void operator>>(K key) {
            remove(*get_by_key(key));
        }

        V *operator[](K key) const {
            return get_by_key(key);
        }
    };
}

#endif //CITY_DEFENCE_REPOSITORY_H
