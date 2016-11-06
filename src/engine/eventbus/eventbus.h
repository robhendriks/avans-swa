//
// Created by robbie on 28-10-2016.
//

#ifndef CITY_DEFENCE_EVENTBUS_H
#define CITY_DEFENCE_EVENTBUS_H

#include <vector>
#include <algorithm>
#include <map>
#include <typeinfo>
#include "any.hpp"
#include "subscriber.h"

namespace engine {
    namespace eventbus {
        class eventbus {
        public:
            static eventbus &get_instance() {
                static eventbus instance;

                return instance;
            }

            template<class T>
            void fire(T &event) {
                for (auto &sub : subscribers[typeid(T).name()]) {
                    sub.as<subscriber<T>*>()->on_event(event);
                }
            }

            template<class T>
            void subscribe(subscriber<T> *subscriber1) {
                subscribers[typeid(T).name()].push_back(subscriber1);
            }

            template<class T>
            void unsubscribe(subscriber<T> *subscriber1) {
                auto &subscribers_array = subscribers[typeid(T).name()];
                for (size_t i = 0; i < subscribers_array.size(); i++) {
                    if (subscribers_array[i].as<subscriber<T>*>() == subscriber1) {
                        subscribers_array.erase(subscribers_array.begin() + i);
                    }
                }
            }

            eventbus(eventbus const &) = delete;

            void operator=(eventbus const &) = delete;

        private:
            std::map<std::string, std::vector<type::any>> subscribers;

            eventbus() {}
        };
    }
}

#endif //CITY_DEFENCE_EVENTBUS_H
