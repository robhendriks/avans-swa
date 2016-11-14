//
// Created by robbie on 12-11-2016.
//

#ifndef CITY_DEFENCE_TESTSUBSCRIBER_H
#define CITY_DEFENCE_TESTSUBSCRIBER_H


#include "TestEvent.h"
#include "../../../../src/engine/eventbus/subscriber.h"

class TestSubscriber : public engine::eventbus::subscriber<TestEvent> {
public:
    TestSubscriber();
    void on_event(TestEvent &event);
    int get_count() const;
private:
    int m_count;
};


#endif //CITY_DEFENCE_TESTSUBSCRIBER_H
