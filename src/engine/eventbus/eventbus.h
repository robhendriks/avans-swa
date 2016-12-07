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
#include <SDL_log.h>
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
                if (event) {
                    // This is needed because a pointer to an event has a different typeid than a reference to an event
                    fire(*event);
                }
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
                m_unsubscribe_count[type_name] = 0;
                std::vector<subscriber<T>*> notified;
                size_t original_size = m_subscribers[type_name].size();
                for (size_t i = 0; i < original_size; i++) {
                    auto &sub = m_subscribers[type_name][i];
                    auto *p_subscriber = sub.as<subscriber<T>*>();
                    // Only notify when not already notified
                    if (std::find(notified.begin(), notified.end(), p_subscriber) == notified.end()) {
                        p_subscriber->on_event(event);
                        notified.push_back(p_subscriber);
                        // When the subscriber, unsubscribes himself start over again
                        if (m_unsubscribe_count[type_name] != 0) {
                            // Start over again with the loop
                            i = 0;

                            // Decrease original_size, so new subscribers won't be notified
                            original_size -= m_unsubscribe_count[type_name];
                            m_unsubscribe_count[type_name] = 0;
                        }
                    }
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
                std::string type_name = typeid(T).name();

                auto &subscribers_array = m_subscribers[type_name];
                for (size_t i = 0; i < subscribers_array.size(); i++) {
                    if (subscribers_array[i].as<subscriber<T>*>() == subscriber1) {
                        subscribers_array.erase(subscribers_array.begin() + i);

                        if (m_unsubscribe_count.find(type_name) != m_unsubscribe_count.end()) {
                            m_unsubscribe_count[typeid(T).name()]++;
                        }

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

            // This is needed to track changes of the m_subscribers map when an event is fired
            std::map<std::string, int> m_unsubscribe_count;

            eventbus() {}
        };
    }
}

#endif //CITY_DEFENCE_EVENTBUS_H
