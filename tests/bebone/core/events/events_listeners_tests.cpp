#include <utility>

#include "bebone/core/core.h"
#include "gtest/gtest.h"

using namespace bebone::core;

enum Category {
    Simple,
    Complex,
    Cool
};

struct SimpleEvent : public Event<Category, Simple> {

};

struct ComplexEvent : public Event<Category, Complex> {
    int field;

    explicit ComplexEvent(const int& field) : field(field) {}
};

struct CoolEvent : public Event<Category, Cool> {
    std::string field;

    explicit CoolEvent(std::string field) : field(std::move(field)) {}
};

TEST(EventListenersTestSuite, FireSingleEvent) {
    EventDispatcher<Category> dispatcher;

    int res = 0;

    dispatcher.add_listener([&](SimpleEvent& event) {
        res += 1;
    });

    dispatcher.fire(SimpleEvent());

    ASSERT_EQ(res, 1);
}

TEST(EventListenersTestSuite, FireEventMultipleTimes) {
    EventDispatcher<Category> dispatcher;

    int res = 0;

    dispatcher.add_listener([&](SimpleEvent& event) {
        res += 1;
    });

    dispatcher.fire(SimpleEvent());
    dispatcher.fire(SimpleEvent());
    dispatcher.fire(SimpleEvent());

    ASSERT_EQ(res, 3);
}

TEST(EventListenersTestSuite, FireMultipleEventsSeveralTimes) {
    EventDispatcher<Category> dispatcher;

    int res = 123;

    dispatcher.add_listener([&](SimpleEvent& event) {
        res += 1;
    });

    dispatcher.add_listener([&](SimpleEvent& event) {
        res -= 1;
    });

    dispatcher.fire(SimpleEvent());
    dispatcher.fire(SimpleEvent());
    dispatcher.fire(SimpleEvent());

    ASSERT_EQ(res, 123);
}

TEST(EventListenersTestSuite, AddDifferentTypesOfEvents) {
    EventDispatcher<Category> dispatcher;

    int res = 0;

    dispatcher.add_listener([&](SimpleEvent& event) {
        res += 1;
    });

    dispatcher.add_listener([&](ComplexEvent& event) {
        res += event.field;
    });

    dispatcher.fire(SimpleEvent());
    dispatcher.fire(SimpleEvent());
    dispatcher.fire(SimpleEvent());

    ASSERT_EQ(res, 3);
}

TEST(EventListenersTestSuite, FireDifferentTypesOfEvents1) {
    EventDispatcher<Category> dispatcher;

    int res = 0;

    dispatcher.add_listener([&](SimpleEvent& event) {
        res += 1;
    });

    dispatcher.add_listener([&](ComplexEvent& event) {
        res += event.field;
    });

    dispatcher.fire(SimpleEvent());
    dispatcher.fire(ComplexEvent(2));

    ASSERT_EQ(res, 3);
}

TEST(EventListenersTestSuite, FireDifferentTypesOfEvents2) {
    EventDispatcher<Category> dispatcher;

    std::string res = "some";

    dispatcher.add_listener([&](SimpleEvent& event) {
        res += "1";
    });

    dispatcher.add_listener([&](ComplexEvent& event) {
        res += to_string(event.field);
    });

    dispatcher.add_listener([&](CoolEvent& event) {
        res += event.field;
    });

    dispatcher.fire(SimpleEvent());
    dispatcher.fire(ComplexEvent(2));
    dispatcher.fire(CoolEvent("poggers"));

    ASSERT_EQ(res, "some12poggers");
}