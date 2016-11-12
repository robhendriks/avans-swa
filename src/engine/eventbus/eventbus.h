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
            /**
             * Get the instance of the eventbus
             *
             * @return eventbus
             */
            static eventbus &get_instance() {
                static eventbus instance;

                return instance;
            }

            /**
             * Fire an event (pointer)
             *
             * @param event
             */
            template<class T>
            void fire(T *event) {
                // This is needed because a pointer to an event has a different typeid than a reference to an event
                fire(*event);
            }

            /**
             * Fire an event (reference)
             *
             * @param event
             */
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

            /**
             * Add a subscriber
             *
             * @param subscriber1
             */
            template<class T>
            void subscribe(subscriber<T> *subscriber1) {
                m_subscribers[typeid(T).name()].push_back(subscriber1);
            }

            /**
             * Add a callback as subscriber
             *
             * NOTE: When calling this with a lambda function you must specify the type for conversion e.g.
             * This will work:
             *      std::function<void(TestEvent &)> callback = [&](TestEvent &event) {};
             *
             *      subscribe("name", callback);
             *
             *  But this will not:
             *      auto callback = [&](TestEvent &event) {};
             *
             *      subscribe("name", callback);
             *
             *  And this will also fail:
             *
             *      subscribe("name", [&](TestEvent &event) {});
             *
             * @param name
             * @param callback
             */
            template<class T>
            void subscribe(std::string name, std::function<void(T)> callback) {
                std::string type_name = typeid(T).name();
                std::string sub_id = type_name + "_callback";
                m_callbacks[name] = sub_id;
                m_subscribers[sub_id].push_back(callback);
            }

            /**
             * Unsubscribe a (class)subscriber
             *
             * @param subscriber1
             */
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

            /**
             * Unsubscribe a callback subscriber
             *
             * @param name
             */
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
