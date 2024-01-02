#include "bebone/bebone.h"

using namespace bebone::core;

void example_function(int x) {
    std::cout << "Example function: " << x << std::endl;
}

void another_function(int x) {
    std::cout << "Another Function: " << x + 40 << std::endl;
}

void meme(int x) {
    std::cout << "emem" << x + 32445 / 23 << std::endl;
}

int main() {

    Action<int> action;
    std::function<void(int)> func = example_function;
    std::function<void(int)> func2 = another_function;
    std::function<void(int)> func3 = meme;

    action += func;
    action += func2;

    action(5);

    action -= func;
    action += func3;

    action(4);

    action -= func2;

    action(0);

    action -= func3;

    action(324);

    return 0;
}
