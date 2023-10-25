#include "bebone/bebone.h"

#include <vector>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

using namespace bebone::gfx;
using namespace bebone::gfx::opengl;

const std::vector<GLfloat> vertices {
    // positions          // colors           // texture coords
    0.5f,  0.5f, 0.0f,    1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
    0.5f, -0.5f, 0.0f,    0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
};

const std::vector<GLuint> indices {
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
};

int main() {
    glfwInit();

    auto window = WindowFactory::create_window("2. OpenGL texture example", SCR_WIDTH, SCR_HEIGHT, GfxAPI::OPENGL);

    GLContext::load_opengl();
    GLContext::set_viewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    auto vertexShader = GLShaderFactory::create_shader("examples/assets/gfx/opengl/2_opengl_texture/vertex.glsl", ShaderTypes::VERTEX_SHADER);
    auto fragmentShader = GLShaderFactory::create_shader("examples/assets/gfx/opengl/2_opengl_texture/fragment.glsl", ShaderTypes::FRAGMENT_SHADER);
    GLShaderProgram shaderProgram(vertexShader, fragmentShader);

    vertexShader.destroy();
    fragmentShader.destroy();
    
    GLVertexArrayObject vao;
    vao.bind();

    GLVertexBufferObject vbo(vertices.data(), vertices.size() * sizeof(GLfloat), GL_STATIC_DRAW);
    GLElementBufferObject ebo(indices.data(), indices.size(), GL_STATIC_DRAW);

    vao.link_attributes(vbo, 0, 3, GL_FLOAT, 8 * (sizeof(float)), (void*)0);
    vao.link_attributes(vbo, 1, 3, GL_FLOAT, 8 * (sizeof(float)), (void*)(3 * sizeof(float)));
    vao.link_attributes(vbo, 2, 2, GL_FLOAT, 8 * (sizeof(float)), (void*)(6 * sizeof(float)));

    vao.unbind();
	vbo.unbind();
	ebo.unbind();

    GLTexture texture("examples/assets/gfx/opengl/2_opengl_texture/awesomeface.png",
        GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

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
        glfwPollEvents();
    }

    vao.destroy();
    vbo.destroy();
    ebo.destroy();
    shaderProgram.destroy();
    texture.destroy();

    glfwTerminate();
    return 0;
}
