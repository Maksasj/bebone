<div>
  <img align="left" src="https://github.com/Maksasj/bebone/blob/master/docs/images/tmpLogo.png" width="288px">
  
  # Bebone
  Bebone - Is a framework/engine aimed for flexible and comfortable game development, written in C++. 
  In other words Bebone is a set of useful game development libraries, written and integrated 
  in Bebone framework ecosystem.
  
  > Bebone is not a new javascript framework btw. It is a game development one!
  
  Cool looking widgets 
  <img src="https://img.shields.io/github/stars/Maksasj/bebone" alt="stars">
  <img src="https://img.shields.io/github/actions/workflow/status/Maksasj/bebone/clang_build_win.yml" alt="build">
  <img src="https://img.shields.io/github/license/Maksasj/bebone" alt="build">
  
  <br>
</div>

# Window Creation
To create a window with specified resolution and api you need to use the create_window method from the WindowFactory static class
```c++
static std::shared_ptr<Window> create_window(const std::string& title, const int& width, const int& height, const GfxAPI& gfxAPI);
```
GfxAPI is a simple enum with supported gfx api. At this moment, Bebone supports only OpenGL and Vulkan. Example usage you can see at the "Hello, World!" examples for the OpenGL and Vulkan (still in development).

# OpenGL
## GLContext
To use a OpenGL context you will need to refer to the GLContext static class. It is a wrapper of the OpenGL context. You will need to use it to initialize OpenGL, set viewport and make other OpenGL context stuff. Example usage is below.
### "Hello, World!" example
```c++
#include "bebone/bebone.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

using namespace bebone::gfx;
using namespace bebone::gfx::opengl;

int main() {
    glfwInit();
    
    auto window = WindowFactory::create_window("0. OpenGL window example", SCR_WIDTH, SCR_HEIGHT, GfxAPI::OPENGL);

    GLContext::load_opengl();
    GLContext::set_viewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    while (!window->closing()) {
        GLContext::clear_color(0.2f, 0.2f, 0.2f, 1.0f);
        GLContext::clear(GL_COLOR_BUFFER_BIT);

        // Your game code resides here
        // ...

        glfwSwapBuffers(window->get_backend());
        GLFWContext::pool_events();
    }

    GLFWContext::terminate();
    return 0;
}
```
In this example, you can see the usage of the WindowFactory and GLContext.
To use these classes and other Bebone features you need to include "bebone/bebone.h".

## Buffer Objects
Bebone supports these OpenGL buffer objects:
* VAO — GLVertexArrayObject
* VBO — GLVertexBufferObject
* EBO — GLElementBufferObject
* UBO — GLUniformBufferObject

All of them are inherited from the abstract GLBufferObject class, that lets to bind, unbind and to destroy buffer objects
```c++
class GLBufferObject : private core::NonCopyable {
        protected:
            GLuint id;

        public:
            GLBufferObject();

            virtual void bind() = 0;
            virtual void unbind() = 0;
            virtual void destroy() = 0;
    };
```

We will now discuss each buffer object separately
### GLVertexArrayObject
To link vertex attributes you will need to use the link_attributes method:
```c++
void link_attributes(GLVertexBufferObject& vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, const u64& offset);
void link_attributes(GLVertexBufferObject& vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
```
VBO is referenced here, to automatically bind and unbind it.

# Vulkan

## Roadmap

### 0.1v Release (This year)
1. **Graphics abstraction layer**. General OpenGL. Window, Monitor apis.
2. **Event system**. Generic event system
3. **Input system**. Event based input system

### 0.1.1v
1. **Asset system**. Basic abstractions for creating/editing image data.

### 0.1.2v
1. **Profiler** General bebone profiler

### 0.2v ...
1. *Scripting*.
2. *Sound system*.
3. *Physics engine*.

## Features
*Todo*

## Build
```bash
cmake -B build -G Ninja

cmake --build build
```

## Testing
```bash
cmake --build build

build\tests\unit\ctest
```

## License
Bebone is free, open source game development framework. All code in this repository FOR NOW is licensed under
- MIT License ([LICENSE.md](https://github.com/Maksasj/bebone/blob/master/LICENSE.md) or https://opensource.org/license/mit/)