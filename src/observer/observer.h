//
// Created by robbie on 26-10-2016.
//

#ifndef CITY_DEFENCE_OBSERVER_H
#define CITY_DEFENCE_OBSERVER_H

namespace observer {
    template <typename T>
    class observer {
    public:
        virtual ~observer() = default;
        virtual void notify(T* p_observee) = 0;
    };
}

#endif //CITY_DEFENCE_OBSERVER_H
