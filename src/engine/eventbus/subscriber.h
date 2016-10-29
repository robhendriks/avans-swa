//
// Created by robbie on 28-10-2016.
//

#ifndef CITY_DEFENCE_SUBSCRIBER_H
#define CITY_DEFENCE_SUBSCRIBER_H

namespace engine {
    namespace eventbus {
        template<class T>
        class subscriber {
        public:
            virtual void on_event(T &event) = 0;
        };
    };
}

#endif //CITY_DEFENCE_SUBSCRIBER_H
