#include "bebone/core/core.h"
#include "test_shared.h"

using namespace bebone::core;

void example_function(int x) {
    std::cout << "Example function: " << x << std::endl;
}

void another_function(int x) {
    std::cout << "Another Function: " << x + 40 << std::endl;
}

void meme(int x) {
    std::cout << "meme function" << x + 32445 / 23 << std::endl;
}

int main() {

    Action<int> action;
    std::function<void(int)> func = example_function;
    std::function<void(int)> func2 = another_function;
    std::function<void(int)> func3 = meme;

    action += func;
    action += func2;

    // subscribed functions: func, func2

    action(5);

    action -= func;
    action += func3;

    // subscribed functions: func2, func3

    action(4);

    action -= func2;

    // subscribed functions: func3

    action(0);

    action -= func3;

    // subscribed functions: none

    action(324);

    return 0;
}