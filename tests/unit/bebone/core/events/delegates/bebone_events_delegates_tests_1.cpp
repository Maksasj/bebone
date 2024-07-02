#include "bebone/core/core.h"
#include "test_shared.h"

using namespace bebone::core;

int main() {
    TEST_CASE {
        Action<int> action;

        int test = 0;

        auto fun = std::function<void(int)>{[&](int value) {
            test += value;
        }};

        action += fun;
        ensure(test == 0);

        action(1);
        ensure(test == 1);

        action(8);
        ensure(test == 9);

        action(8);
        ensure(test == 17);

        action -= fun;

        action(8);
        ensure(test == 17);
    }

    TEST_CASE {
        Action<> action;

        int test = 0;

        auto fun0 = std::function<void()>{[&]() {
            test += 1;
        }};

        auto fun1 = std::function<void()>{[&]() {
            test += 3;
        }};

        action += fun0;
        action += fun1;

        ensure(test == 0);

        action();
        ensure(test == 4);

        action();
        ensure(test == 8);
    }

    TEST_CASE {
        Action<> action;

        int test0 = 0;
        int test1 = 0;

        auto fun0 = std::function<void()>{[&]() {
            test0 += 1;
        }};

        auto fun1 = std::function<void()>{[&]() {
            test1 += 3;
        }};

        action += fun0;
        action += fun1;

        ensure(test0 == 0);
        ensure(test1 == 0);

        action();
        ensure(test0 == 1);
        ensure(test1 == 3);

        action();
        ensure(test0 == 2);
        ensure(test1 == 6);
    }

    return 0;
}