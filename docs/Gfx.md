
## Graphics module

### Window Creation
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

    GLFWContext::terminate();
    return 0;
}
```

## Textures
To create and load textures using OpenGL Bebone you will need to use GLTexture class. Texture creation is simple:
```c++
GLTexture(const char* image, const GLenum& textureType, const GLenum& format, const GLenum& pixelType);
```
You only need to specify the image path, texture type (1D/2D/3D), RGB format and pixel type (data type). You can bind/unbind/destroy the texture in the same way like with buffer objects.

Also, there are some helper functions:
```c++
void bind_texture_unit(const GLuint& textureUnit);

// in pixels
int get_width() const;
int get_height() const;
```
If you want to bind texture to the specific texture unit you can use bind_texture_unit method.

Example usage for thess methods you can find in the "Flappy Bird example".

### Texture example
```c++
#include "bebone/bebone.h"

#include <vector>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

using namespace bebone::gfx;
using namespace bebone::gfx::opengl;

struct Vertex {
    Vec3f pos;
    Vec3f color;
    Vec2f texCord;
};

const std::vector<Vertex> vertices {
    {{0.5f,  0.5f, 0.0f},    {1.0f, 0.0f, 0.0f},   {1.0f, 1.0f}},
    {{0.5f, -0.5f, 0.0f},    {0.0f, 1.0f, 0.0f},   {1.0f, 0.0f}},
    {{-0.5f, -0.5f, 0.0f},   {0.0f, 0.0f, 1.0f},   {0.0f, 0.0f}},
    {{-0.5f,  0.5f, 0.0f},   {1.0f, 1.0f, 0.0f},   {0.0f, 1.0f}}
};

const std::vector<u32> indices {
    0, 1, 3,
    1, 2, 3
};

int main() {
    GLFWContext::init();

    auto window = WindowFactory::create_window("2. OpenGL texture example", SCR_WIDTH, SCR_HEIGHT, GfxAPI::OPENGL);

    GLContext::load_opengl();
    GLContext::set_viewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    auto vertexShader = GLShaderFactory::create_shader("vertex.glsl", ShaderTypes::VERTEX_SHADER);
    auto fragmentShader = GLShaderFactory::create_shader("fragment.glsl", ShaderTypes::FRAGMENT_SHADER);
    GLShaderProgram shaderProgram(vertexShader, fragmentShader);

    vertexShader.destroy();
    fragmentShader.destroy();
    
    GLVertexArrayObject vao;
    vao.bind();

    GLVertexBufferObject vbo(vertices.data(), vertices.size() * sizeof(Vertex));
    GLElementBufferObject ebo(indices.data(), indices.size() * sizeof(u32));

    vao.link_attributes(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, pos));
    vao.link_attributes(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, color));
    vao.link_attributes(vbo, 2, 2, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, texCord));

    vao.unbind();
	vbo.unbind();
	ebo.unbind();

    GLTexture texture("awesomeface.png",GL_TEXTURE_2D, GL_RGBA, GL_UNSIGNED_BYTE);

    shaderProgram.set_uniform("ourTexture", 0);

    GLContext::enable(GL_CULL_FACE);
    GLContext::cull_face(GL_BACK);
    GLContext::front_face(GL_CW);

    while (!window->closing()) {
        GLContext::clear_color(0.2f, 0.2f, 0.2f, 1.0f);
        GLContext::clear(GL_COLOR_BUFFER_BIT);

        shaderProgram.enable();

        texture.bind();
        vao.bind();

        GLContext::draw_elements(GL_TRIANGLES, static_cast<i32>(indices.size()), GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(window->get_backend());
        GLFWContext::poll_events();
    }

    GLFWContext::terminate();

    return 0;
}
```

## Vulkan
*This section is still in development.*