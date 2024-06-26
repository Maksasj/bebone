#include <utility>

#include "bebone/core/core.h"
#include "test_shared.h"

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

int main() {
    TEST_CASE {
        EventDispatcher<Category> dispatcher;

        int res = 0;

        dispatcher.add_listener([&](SimpleEvent& event) {
            res += 1;
        });

        dispatcher.fire(SimpleEvent());

        ensure(res == 1);
    }

    TEST_CASE {
        EventDispatcher<Category> dispatcher;

        int res = 0;

        dispatcher.add_listener([&](SimpleEvent& event) {
            res += 1;
        });

        dispatcher.fire(SimpleEvent());
        dispatcher.fire(SimpleEvent());
        dispatcher.fire(SimpleEvent());

        ensure(res == 3);
    }

    TEST_CASE {
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

        ensure(res == 123);
    }

    TEST_CASE {
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

        ensure(res == 3);
    }

    TEST_CASE {
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

        ensure(res == 3);
    }

    TEST_CASE {
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

        ensure(res == "some12poggers");
    }

    return 0;
}