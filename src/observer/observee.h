//
// Created by robbie on 26-10-2016.
//

#ifndef CITY_DEFENCE_OBSERVEE_H
#define CITY_DEFENCE_OBSERVEE_H

#include "observer.h"
#include <vector>

namespace observer {
    template <typename T>
    class observee {
    public:
        virtual ~observee() = default;

        bool add_observer(observer<T>* p_observer) {
            auto temp = find(m_observers.begin(), m_observers.end(), p_observer);
            if (temp != m_observers.end()) {
                return false;
            }

            m_observers.push_back(p_observer);
            return true;
        }

        void remove_observer(observer<T>* p_observer) {
            m_observers.erase(remove(m_observers.begin(), m_observers.end(), p_observer));
        }

        void notify_observers(T* obj) {
            for (auto observer : m_observers) {
                observer->notify(obj);
            }
        }
    private:
        std::vector<observer<T>*> m_observers;
    };
}

#endif //CITY_DEFENCE_OBSERVEE_H
