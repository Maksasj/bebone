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
    * Action system (C# style)
  * Input system
  * Meta programming module
* Graphics module
  * OpenGL abstraction layer
  * Vulkan abstraction layer(in development)
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

## Window Creation
To create a window with specified resolution and api you need to use the create_window method from the WindowFactory static class
```c++
static std::shared_ptr<Window> create_window(const std::string& title, const int& width, const int& height, const GfxAPI& gfxAPI);
```
GfxAPI is a simple enum with supported gfx api. At this moment, Bebone supports only OpenGL and Vulkan. Example usage you can see at the "Hello, World!" examples for the OpenGL and Vulkan (still in development).

## OpenGL
### GLContext
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
VBO is referenced here to automatically bind and unbind it.

### GLVertexBufferObject and GLElementBufferObject
In the VBO/EBO constructor you can specify the data and the buffer object usage. Usage specifies the expected usage pattern of the data store. Only GL_STATIC_DRAW and GL_DYNAMIC_DRAW have been tested. Other symbolic constants like GL_STATIC_READ, GL_STATIC_COPY, GL_DYNAMIC_READ, etc. have not been tested yet.
```c++
GLVertexBufferObject(const void* vertices, const GLsizeiptr& size, const GLenum& usage = GL_STATIC_DRAW);
GLElementBufferObject(const void* indices, const GLsizeiptr& size, const GLenum& usage = GL_STATIC_DRAW);
```
From the usage depends could you call the buffer_sub_data in the VBO/EBO or not.
```c++
void buffer_sub_data(const GLintptr& offset, const GLsizeiptr& size, const void* data);
```
This function calls glBufferSubData and works accordingly

### GLUniformBufferObject
GLUniformBufferObject - class used for creating an opengl uniform buffer objects. UBO is a Buffer Object that stores uniform data for a shader program. UBOs can be used to share uniforms between different programs, and to quickly switch between sets of uniforms for the same program object.

Lets look onto GLUniformBufferObject constructor
```c++
GLUniformBufferObject(const u64& _size);
```
As you see UBO object require only size to be specified during object creation. If you want to upload any data to UBO, firstly you need to bind it:
```c++
buffer.bind();
shaderProgram.bind_buffer("ubo", 1, buffer);

int* mapped = (int*) buffer.map();
(*mapped) = 5;

cameraUbo.unmap();
cameraUbo.unbind();
```
After, you need to bind your UBO to specific shader binding using `shaderProgram.bind_buffer()`, after you can map buffer. Buffer `.map()` method returns void* pointer to mapped memory region. After, this void pointer can be used for uploading any data to yours UBO. After you done with all data, you can simply unmap and unbind your buffer.

## Shaders
To use shaders in OpenGL Bebone you will need to use the GLShaderFactory, GLShader, GLShaderProgram classes.

### GLShaderFactory
GLShaderFactory creates shader objects (GLShader) which later need to be assigned to the shader program (GLShaderProgram). GLShaderFactory has only one public method for shader creation:
```c++
static GLShader create_shader(const std::string& path, const ShaderType& shaderType, const GLShaderProperties& properties = NONE);
```
You need to specify the path to the glsl shader, it's type (vertex/fragment shader) and other properties (enable uniforms or not)

Simple example usage:
```c++
GLShader vertexShader = GLShaderFactory::create_shader("vertex.glsl", ShaderTypes::VERTEX_SHADER);
GLShader fragmentShader = GLShaderFactory::create_shader("fragment.glsl", ShaderTypes::FRAGMENT_SHADER);
```

### GLShader
In OpenGL, a Shader is a user-defined program designed to run on some stage of a graphics processor. Shaders provide the code for certain programmable stages of the rendering pipeline and can also be used in a slightly more limited form for general, on-GPU computation.

Firstly lets create our shader. The easiest and simplest way to create a shader is to use GLShaderFactory, like this:
```c++
auto vertexShader = GLShaderFactory::create_shader("vertex.glsl", ShaderTypes::VERTEX_SHADER);
auto fragmentShader = GLShaderFactory::create_shader("fragment.glsl", ShaderTypes::FRAGMENT_SHADER);
```
As you see you need only to specify path to shader source code and shader type, after this you can use your shader for creating your shader program.

Second way is using GLShader constructor:
```c++
GLShader(const ShaderCode& code, const ShaderType& shaderType, const GLShaderProperties& properties = NONE);
```
As you see there you have a bit more controll on creating your opengl shader. You can compile your opengl shader code manually using ShaderCompiler and then use shader code as input for GLShader constructor.

### GLShaderProgram
To create a shader program you need to create vertex and fragment shaders with GLShaderFactory.
```c++
GLShaderProgram shaderProgram(vertexShader, fragmentShader);
```
You can enable/destroy it and set uniforms. To set uniforms you will need to call the set_uniform method. Bebone supports only these uniforms now:
```c++
void set_uniform(const char* uniformName, const i32& value) const;
void set_uniform(const char* uniformName, const GLsizei& size, const i32* value) const;
void set_uniform(const char* uniformName, const u32& value) const;
void set_uniform(const char* uniformName, const f32& value) const;
void set_uniform(const char* uniformName, const Mat4f& value) const;
```

### "Hello, Triangle!" example
Using all aforementioned API, you can display your first triangle as follows:
```c++
#include <vector>

#include "bebone/bebone.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

using namespace bebone::gfx;
using namespace bebone::gfx::opengl;

const std::vector<Vec3f> vertices = {
    {-0.5f, -0.5f, 0.0f},
    {0.5f, -0.5f, 0.0f},
    {0.0f,  0.5f, 0.0f}
};

const std::vector<u32> indices = {
	0, 1, 2,
};

int main() {
    GLFWContext::init();

    auto window = WindowFactory::create_window("1. OpenGL hello triangle example", SCR_WIDTH, SCR_HEIGHT, GfxAPI::OPENGL);

    GLContext::load_opengl();
    GLContext::set_viewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    GLShader vertexShader = GLShaderFactory::create_shader("vertex.glsl", ShaderTypes::VERTEX_SHADER);
    GLShader fragmentShader = GLShaderFactory::create_shader("fragment.glsl", ShaderTypes::FRAGMENT_SHADER);
    GLShaderProgram shaderProgram(vertexShader, fragmentShader);

    vertexShader.destroy();
    fragmentShader.destroy();
    
    GLVertexArrayObject vao;
    vao.bind();

    GLVertexBufferObject vbo(vertices.data(), vertices.size() * sizeof(Vec3f));
    GLElementBufferObject ebo(indices.data(), indices.size() * sizeof(u32));

    vao.link_attributes(vbo, 0, 3, GL_FLOAT, sizeof(Vec3f), nullptr);

    vao.unbind();
	vbo.unbind();
	ebo.unbind();

    while(!window->closing()) {
        GLContext::clear_color(0.2f, 0.2f, 0.2f, 1.0f);
        GLContext::clear(GL_COLOR_BUFFER_BIT);

        shaderProgram.enable();
        vao.bind();
        GLContext::draw_arrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window->get_backend());
        GLFWContext::poll_events();
    }

    vao.destroy();
    vbo.destroy();
    ebo.destroy();
    shaderProgram.destroy();

    GLFWContext::terminate();
    return 0;
}
```

## Textures
To create and load textures using OpenGL Bebone you will need to use GLTexture class.

## Vulkan
*This section is still in development.*

## License
Bebone is free, open source game development framework. All code in this repository FOR NOW is licensed under
- MIT License ([LICENSE.md](https://github.com/Maksasj/bebone/blob/master/LICENSE.md) or https://opensource.org/license/mit/)