# bebone 💀

Modular game development framework/engine written with **C++**. **Bebone** implements **high-level** abstractions, as well as provides access to **low-level** internal abstractions for **flexible** and **highly customizable** game development

- **Modular code base**, every **bebone** module is a self contained library with **minimal** dependency on **third-party** libraries. All **bebone** abstractions inherit same **interfaces**, for better integration with user defined abstractions   
- **Designed with real-world use in mind** for small hobby projects, as well as professional/enterprise projects. 
- **User-Friendly** for **all experience levels**. Designed to be intuitive and easy to use for **beginners**, as well as experienced professionals

> **Bebone** is not a new javascript framework btw. It is a game development one!

Cool looking widgets 
![GitHub Repo stars](https://img.shields.io/github/stars/Maksasj/bebone)
![GitHub Actions Workflow Status](https://img.shields.io/github/actions/workflow/status/Maksasj/bebone/clang_build_win.yml)
![GitHub License](https://img.shields.io/github/license/Maksasj/bebone)
![Discord](https://img.shields.io/discord/1156584129190711326?logo=discord)

### Links
1. Source code available at [github.com/Maksasj/bebone](https://github.com/Maksasj/bebone)
2. Community Discord [discord.gg/bebone](https://discord.gg/v4mcTmuDTb)
3. **Bebone** documentation available at [github.com/Maksasj/bebone](github.com/Maksasj/bebone/docs/DOCUMENTATION.md)

## Architecture

**Bebone** provides multi layer APIs where each level build on top of previous:

- **[Abstraction]()** basic abstraction layer, abstracts most basic things, such as OpenGL or Vulkan
- **[System]()** advance abstraction layer, implements generalized systems on top of **abstraction layer**, such as **Renderer**
- **[App]()** - complete application layer, combines multiple systems into self-contained application 



## Features

For now **bebone** have severall modules:

* [Core module](). Core **bebone** module implements most important abstractions which are widely used across all other modules. Implements **Memory, Debug, Types, Event, Input** abstractions
* [Graphics module (GFX module)](). **Abstraction layer** module, implements basic abstractions on top of **Graphical APIs** such as **OpenGL** and **Vulkan**. **GFX module**
 depends on **Core**, **Assets** modules
* [Assets module](). Module designed for loading and managing different **assets** such as **images**, **models**, **materals**. **Assets module** depends on **Core module** only 
* [Renderer module]() **System layer** module, provides high-level generalized graphical functionality. It abstracts all low-level **OpenGL** or **Vulkan** under one convenient interface. **Renderer module** build on top of **GFX module**

### Planned modules

* [Sound module]()
* [Physics module]()
* [Entity component system module (ECS module)]()
* [App module]()

## Build
For now there is only one build method

### Build manually

First of all requirements
  - [CMake](https://cmake.org/) (At least version 3.21)
  - [Ninja](https://github.com/ninja-build/ninja) (At least version 1.11.1)
  - C++ compiler (Have test with Clang 15.0.5 and GCC 12.2.0) 
  - *[Vulkan SDK](https://www.lunarg.com/vulkan-sdk/) (if you want to build [GFX module]())*

  Firstly lets clone **bebone** locally *(note that you also need to clone all bebone git submodules)*

  ```bash
  git clone --recursive git@github.com:Maksasj/bebone.git
  ```

  Secondly lets configure our **CMake** configuration with
  ```bash
  cmake -B build -G Ninja
  ```

  Finally you can simply build project with cmake 
  ```bash
  cmake --build build
  ```

## Testing
### Unit testing
The testing process is similar to the **Building**. After a successful build, all you have to do is run [CTest](https://cmake.org/cmake/help/book/mastering-cmake/chapter/Testing%20With%20CMake%20and%20CTest.html) from ```build\tests\unit``` directory

### Integration testing
As for integration tests we use our examples, so see **[Examples]() section**

## Dependencies
For convenience, we tried to reduce the use of third-party libraries, as it complicates code management and readability.
At the moment, bebone is only dependent on these third-party libraries:
  - [Glad](https://github.com/Maksasj/glad/tree/all-extensions) *(OpenGL function header)*
  - [Vulkan-Headers](https://github.com/Maksasj/Vulkan-Headers/tree/main) *(Vulkan function header)*
  - [GLFW](https://github.com/Maksasj/glfw/tree/master) *(Window management library)*
  - [Glslang](https://github.com/KhronosGroup/glslang/tree/main) *(SPIR-V shader compiler library)* 
  - [imgui](https://github.com/Maksasj/imgui/tree/master) *(Debug GUI library)* 
  - [stb](https://github.com/Maksasj/stb/tree/master) *(Image management library and others)* 
  - [miniaudio](https://github.com/Maksasj/miniaudio/tree/master) *(Sound and Music library)*

## Examples
You can find examples in [examples](https://github.com/Maksasj/bebone/tree/master/examples) directory.

## Documentation
  - [Core module](https://github.com/Maksasj/bebone/blob/master/docs/core/CORE.md)
  - [Assets module](https://github.com/Maksasj/bebone/blob/master/docs/assets/ASSETS.md)
  - [GFX module](https://github.com/Maksasj/bebone/blob/master/docs/gfx/GFX.md)
  - [Renderer module](https://github.com/Maksasj/bebone/blob/master/docs/renderer/RENDERER.md)

For full documentation see [DOCUMENTATION.md](https://github.com/Maksasj/bebone/blob/master/docs/DOCUMENTATION.md) file

## Contribution
Since for now no one cares about **bebone** we do not have any instructions or pull request templates, so just open [issue](https://github.com/Maksasj/bebone/issues) or something.

## License
**Bebone** is free and open source game development framework. All code in this repository **FOR NOW** is licensed under
-  Apache-2.0 license ([LICENSE.md](https://github.com/Maksasj/bebone/blob/master/LICENSE.md) or http://www.apache.org/licenses/LICENSE-2.0)

*Copyright 2023-9999 © Maksim Jaroslavcevas, Oskaras Vištorskis*