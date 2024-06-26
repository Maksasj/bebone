# bebone

**bebone** is a game development framework/engine aimed for flexible and comfortable game development, written in **C++**.

- **Modular code base**, every **bebone** module is a self contained library with **minimal** dependency on **third-party** libraries. All **bebone** abstractions inherit same **interfaces**, for better integration with user defined abstractions   

- **Designed with real-world use in mind** for small hobby projects, as well as professional/enterprise projects. **bebone** provides multi layer APIs **Abstraction -> System -> App** levels, where each level build on top of previous 

### Links
1. Source code available at [github.com/Maksasj/bebone](https://github.com/Maksasj/bebone)
2. Community Discord [link](https://discord.gg/v4mcTmuDTb)
3. **bebone** documentation available at [link](github.com/Maksasj/bebone/docs/DOCUMENTATION.md)

> **bebone** is not a new javascript framework btw. It is a game development one!

Cool looking widgets 
![GitHub Repo stars](https://img.shields.io/github/stars/Maksasj/bebone)
![GitHub Actions Workflow Status](https://img.shields.io/github/actions/workflow/status/Maksasj/bebone/clang_build_win.yml)
![GitHub License](https://img.shields.io/github/license/Maksasj/bebone)
![Discord](https://img.shields.io/discord/1156584129190711326?style=flat&label=discord)

### Architecture

In other words **bebone** is modular game development framework, where each module is a self contained library, that can be used apart from the entire framework

## Features
For now **bebone** have severall modules
* [Core module](). Core **bebone** module implements most important abstractions which are widely used across all other modules. Implements **Memory, Debug, Types, Event, Input** abstractions
* [Graphics module (GFX module)](). **Abstraction layer** module, implements basic abstractions on top of **Graphical APIs** such as **OpenGL** and **Vulkan**. **GFX module**
 depends on **Core**, **Assets** modules
* [Assets module](). Module designed for loading and managing different **assets** such as **images**, **models**, **materals**. **Assets module** depends on Core module only 
* [Renderer module]() **System layer** module, provides high-level generalized graphical functionality. It abstracts all low-level **OpenGL** or **Vulkan** under one convenient interface. **Renderer module** build on top of **GFX module**

### Planned modules
* [Sound module]()
* [Physics module]()
* [Entity component system module (ECS module)]()
* [App module]()

## Build
For now there is one method how you can use bebone is your project

### Build manually

First of all requirements
  - [CMake]() (At least version 3.21)
  - [Ninja]() (At least version 1.11.1)
  - C++ compiler (Have test with Clang 15.0.5 and GCC 12.2.0) 
  - *Vulkan SDK (if you want to build [GFX module]())*

  Firstly lets clone bebone locally *(note that you also need to clone all bebone git submodules)*

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
Bebone hello world example:
You can find examples in [examples](https://github.com/Maksasj/bebone/tree/master/examples) directory.

## Documentation
  - [Core module](https://github.com/Maksasj/bebone/blob/master/docs/Core.md)
  - [GFX module](https://github.com/Maksasj/bebone/blob/master/docs/Gfx.md)

## Contribution
Todo

## License
**bebone** is free and open source game development framework. All code in this repository **FOR NOW** is licensed under
-  Apache-2.0 license ([LICENSE.md](https://github.com/Maksasj/bebone/blob/master/LICENSE.md) or http://www.apache.org/licenses/LICENSE-2.0)

*Copyright 2019-2022 © Maksim Jaroslavcevas, Oskaras Vištorskis*