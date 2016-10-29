//
// Created by robbie on 28-10-2016.
//

#ifndef CITY_DEFENCE_EVENTBUS_H
#define CITY_DEFENCE_EVENTBUS_H

#include <vector>
#include <algorithm>
#include <map>
#include "subscriber.h"

namespace engine {
    namespace eventbus {
        template<class T>
        class eventbus {
        public:
            static eventbus &get_instance() {
                static eventbus instance;

                return instance;
            }

            void fire(T &event) {
                for (auto &subscriber : subscribers) {
                    subscriber->on_event(event);
                }
            }

            void subscribe(subscriber <T> *subscriber1) {
                subscribers.push_back(subscriber1);
            }

            void unsubscribe(subscriber<T> *subscriber1) {
                auto find = std::find(subscribers.begin(), subscribers.end(), subscriber1);
                if (find != subscribers.end()) {
                    subscribers.erase(find);
                }
            }

            eventbus(eventbus const &) = delete;

            void operator=(eventbus const &) = delete;

        private:
            std::vector<subscriber<T>*> subscribers;

            eventbus() {}
        };
    }
}

#endif //CITY_DEFENCE_EVENTBUS_H
