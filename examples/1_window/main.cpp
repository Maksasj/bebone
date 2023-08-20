#include <iostream>
#include <thread>

#include "bebone.h"

using namespace bebone::gfx;
using namespace bebone::core;

int main() {
    RenderingEngine::preinit();
        
    Window window("Window example");

    while (!window.closing()) {

        glfwPollEvents();
    }

    RenderingEngine::terminate();
    return 0;
}
