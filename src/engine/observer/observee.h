//
// Created by robbie on 26-10-2016.
//

#ifndef CITY_DEFENCE_OBSERVEE_H
#define CITY_DEFENCE_OBSERVEE_H

#include "observer.h"
#include <string>
#include <vector>

namespace engine {
    namespace observer {
        template<typename T>
        class observee {
        public:
            virtual ~observee() = default;

            /**
             * Add a new observer to the obeservee
             *
             * @param p_observer
             * @return bool - false when the observer is already added
             */
            bool add_observer(observer <T> *p_observer) {
                // Check if the observer is already added
                auto temp = find(m_observers.begin(), m_observers.end(), p_observer);
                if (temp != m_observers.end()) {
                    return false;
                }

                // Not added yet: add it to the list
                m_observers.push_back(p_observer);

                return true;
            }

            /**
             * Remove an observer from the list
             *
             * @param p_observer
             */
            void remove_observer(observer <T> *p_observer) {
                m_observers.erase(remove(m_observers.begin(), m_observers.end(), p_observer));
            }

            /**
             * Notify all the observers
             *
             * @param obj - the observee object
             * @param type
             */
            void notify_observers(T *obj, std::string type = "") {
                for (auto &observer : m_observers) {
                    if (observer)
                        observer->notify(obj, type);
                }
            }

        private:
            std::vector<observer < T>*> m_observers;
        };
    }
}

#endif //CITY_DEFENCE_OBSERVEE_H
