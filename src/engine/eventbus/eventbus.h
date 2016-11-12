//
// Created by robbie on 28-10-2016.
//

#ifndef CITY_DEFENCE_EVENTBUS_H
#define CITY_DEFENCE_EVENTBUS_H

#include <vector>
#include <algorithm>
#include <map>
#include <typeinfo>
#include <functional>
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
            void fire(T *event) {
                // This is needed because a pointer to an event has a different typeid than a reference to an event
                fire(*event);
            }

            template<class T>
            void fire(T &event) {
                std::string type_name = typeid(T).name();

                // Loop for "normal" m_subscribers
                for (auto &sub : m_subscribers[type_name]) {
                    sub.as<subscriber<T>*>()->on_event(event);
                }

                // Loop for callbacks
                for (auto &sub : m_subscribers[type_name + "_callback"]) {
                    auto callback = sub.as<std::function<void(T)>>();
                    callback(event);
                }
            }

            template<class T>
            void subscribe(subscriber<T> *subscriber1) {
                m_subscribers[typeid(T).name()].push_back(subscriber1);
            }

            template<class T>
            void subscribe(std::string name, std::function<void(T)> callback) {
                std::string type_name = typeid(T).name();
                std::string sub_id = type_name + "_callback";
                m_callbacks[name] = sub_id;
                m_subscribers[sub_id].push_back(callback);
            }

            template<class T>
            void unsubscribe(subscriber<T> *subscriber1) {
                auto &subscribers_array = m_subscribers[typeid(T).name()];
                for (size_t i = 0; i < subscribers_array.size(); i++) {
                    if (subscribers_array[i].as<subscriber<T>*>() == subscriber1) {
                        subscribers_array.erase(subscribers_array.begin() + i);
                        return;
                    }
                }
            }

            void unsubscribe(std::string name) {
                if (m_callbacks.find(name) != m_callbacks.end()) {
                    m_subscribers.erase(m_callbacks[name]);
                    m_callbacks.erase(name);
                }
            }

            eventbus(eventbus const &) = delete;

            void operator=(eventbus const &) = delete;

        private:
            std::map<std::string, std::string> m_callbacks;
            std::map<std::string, std::vector<type::any>> m_subscribers;

            eventbus() {}
        };
    }
}

#endif //CITY_DEFENCE_EVENTBUS_H
