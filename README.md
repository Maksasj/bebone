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
TODO

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
TODO

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