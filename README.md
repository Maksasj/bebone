# Bebone
Bebone - Is a framework/engine aimed for flexible and comfortable game development, written in C++. 
In other words Bebone is a set of useful game development libraries, written and integrated 
in Bebone framework ecosystem.

> Bebone is not a new javascript framework btw. It is a game development one!

Cool looking widgets 
<img src="https://img.shields.io/github/stars/Maksasj/bebone" alt="stars">
<img src="https://img.shields.io/github/actions/workflow/status/Maksasj/bebone/clang_build_win.yml" alt="build">
<img src="https://img.shields.io/github/license/Maksasj/bebone" alt="build">

## Features
* Core module
  * Arena allocator & container
  * Logger
  * Types library
  * Event submodule
    * Listener system (Java style)
    * Action delegate (C# style)
  * Input system
  * Meta programming module
* Graphics module
  * OpenGL abstraction layer
  * Vulkan abstraction layer (in development)
  * Shaders
  * Window
  * Begui (Dear ImGui abstraction layer)
## Build
For now there is two methods how you can use bebone is your project(build locally).
1. **Build manually**<br>
  First of all requirements:
    - Cmake (At least version 3.21)
    - Ninja (At least version 1.11.1)
    - C++ compiler (Have test with Clang 15.0.5 and GCC 12.2.0) 
    - *Vulkan SDK (if you want to build gfx module)*
  
    Firstly lets clone bebone locally(note that you also need to clone all bebone git submodules).

    Secondly lets configure our Cmake configuration with
    ```bash
    cmake -B build -G Ninja
    ```

    Finally you can simply build project with cmake 
    ```bash
    cmake --build build
    ```

2. **Using docker**<br>
    Currently the docker image is not available, but we are planning to release it towards bebone 0.2v.

Note that bebone is only a **set** of useful libraries/modules, some modules can be used separately.

## Testing
The testing process is similar to the **Building**. After a successful build, all you have to do is run CTest from ```build\tests\unit``` directory.

## Dependencies
For convenience, we try to reduce the use of third-party libraries, as it complicates code management and readability.
At the moment, bebone is only dependent on these libraries:
  - [Glad](https://github.com/Maksasj/glad/tree/all-extensions) *(opengl function header)*
  - [Vulkan-Headers](https://github.com/Maksasj/Vulkan-Headers/tree/main) *(vulkan function header)*
  - [GLFW](https://github.com/Maksasj/glfw/tree/master) *(window management library)*
  - [Glslang](https://github.com/KhronosGroup/glslang/tree/main) *(SPIR-V shader compiler library)* 
  - [imgui](https://github.com/Maksasj/imgui/tree/master) *(Debug gui library)* 
  - [omni_types](https://github.com/Maksasj/omni_types/tree/master) *(Type library)* 
  - [stb](https://github.com/Maksasj/stb/tree/master) *(Image management library and others)* 

## Examples
Bebone hello world example:
```c++
#include "bebone/bebone.h"

using namespace bebone::gfx;
using namespace bebone::gfx::opengl;

int main() {
    GLFWContext::init();
    
    auto window = WindowFactory::create_window("Example", 800, 600, GfxAPI::OPENGL);

    GLContext::load_opengl();
    GLContext::set_viewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    while (!window->closing()) {
        GLContext::clear_color(0.2f, 0.2f, 0.2f, 1.0f);
        GLContext::clear(GL_COLOR_BUFFER_BIT);

        // Your game code

        GLFWContext::swap_buffers(*window);
        GLFWContext::poll_events();
        window->execute_input_actions();
    }

    GLFWContext::terminate();
    return 0;
}

```

You can find other OpenGL examples in [examples/gfx/opengl](https://github.com/Maksasj/bebone/tree/docs/examples) directory.

## Documentation
  - [Core module]()
  - [GFX module]()

## License
Bebone is free, open source game development framework. All code in this repository FOR NOW is licensed under
- MIT License ([LICENSE.md](https://github.com/Maksasj/bebone/blob/master/LICENSE.md) or https://opensource.org/license/mit/)