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

    GLShader vertexShader = GLShaderFactory::create_shader("vertex.glsl", ShaderTypes::vertex_shader);
    GLShader fragmentShader = GLShaderFactory::create_shader("fragment.glsl", ShaderTypes::fragment_shader);
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

