#include "bebone/bebone.h"

using namespace bebone::core;

void example_function(int x) {
    std::cout << "Example function: " << x << std::endl;
}

void another_function(int x) {
    std::cout << "Another Function: " << x + 40 << std::endl;
}

int main() {
    Action<int> action;

    auto exampleFunction = std::make_shared<std::function<void(int)>>(example_function);
    auto anotherFunction = std::make_shared<std::function<void(int)>>(another_function);
    auto lambdaFunction = std::make_shared<std::function<void(int)>>([](int x) {
        std::cout << "Lambda Function: " << x << std::endl;
    });

    action += exampleFunction;
    action += anotherFunction;
    action += lambdaFunction;
    action(42);

    action -= exampleFunction;
    action(0);

    action -= anotherFunction;
    action(34);

    action -= lambdaFunction;
    action(21);

    return 0;
}
