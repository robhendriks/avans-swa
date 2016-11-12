//
// Created by robbie on 12-11-2016.
//

#include "gtest/gtest.h"
#include "../../../src/engine/eventbus/eventbus.h"
#include "test_classes/TestEvent.h"
#include "test_classes/TestSubscriber.h"

/**
 * Callback subscriber test
 */
TEST(eventbus, callback_subscriber_test) {
    auto &bus = engine::eventbus::eventbus::get_instance();

    int call_count = 0;
    std::function<void(TestEvent &)> callback = [&](TestEvent &event) {
        call_count++;
    };

    bus.subscribe("callback", callback);

    auto *event = new TestEvent();
    bus.fire(event);
    EXPECT_EQ(1, call_count);
    bus.fire(event);
    EXPECT_EQ(2, call_count);

    // Unsubscribe
    bus.unsubscribe("callback");

    // Because the callback is unsubscribed it should not be called anymore
    bus.fire(event);
    EXPECT_EQ(2, call_count);

    delete event;
}

/**
 * Class subscriber test
 */
TEST(eventbus, class_subscriber_test) {
    auto &bus = engine::eventbus::eventbus::get_instance();

    auto *subscriber1 = new TestSubscriber();
    bus.subscribe(subscriber1);

    auto *event = new TestEvent();
    bus.fire(event);
    EXPECT_EQ(1, subscriber1->get_count());
    bus.fire(event);
    EXPECT_EQ(2, subscriber1->get_count());

    // Unsubscribe
    bus.unsubscribe(subscriber1);

    // Because subscriber1 is unsubscribed it should not be called anymore
    bus.fire(event);
    EXPECT_EQ(2, subscriber1->get_count());

    delete subscriber1;
    delete event;
}
