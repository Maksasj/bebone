#include "bebone/core/core.h"
#include "gtest/gtest.h"

using namespace bebone::core;

TEST(DelegateTestSuite, PerformingSingleActionTest) {
    Action<int> action;

    int test = 0;

    auto fun = std::function<void(int)>{[&](int value) {
        test += value;
    }};

    action += fun;
    ASSERT_EQ(test, 0);

    action(1);
    ASSERT_EQ(test, 1);

    action(8);
    ASSERT_EQ(test, 9);

    action(8);
    ASSERT_EQ(test, 17);

    action -= fun;

    action(8);
    ASSERT_EQ(test, 17);
}

TEST(DelegateTestSuite, PerformingMultipleActionsTest) {
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

    ASSERT_EQ(test, 0);

    action();
    ASSERT_EQ(test, 4);

    action();
    ASSERT_EQ(test, 8);
}