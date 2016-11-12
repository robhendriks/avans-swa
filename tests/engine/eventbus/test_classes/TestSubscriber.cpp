//
// Created by robbie on 12-11-2016.
//

#include "TestSubscriber.h"

TestSubscriber::TestSubscriber() : m_count(0) {

}

void TestSubscriber::on_event(TestEvent &event) {
    m_count++;
}

int TestSubscriber::get_count() const {
    return m_count;
}
