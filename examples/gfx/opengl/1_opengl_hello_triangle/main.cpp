#include <vector>

#include "bebone/bebone.h"

const unsigned int screen_width = 800;
const unsigned int screen_height = 600;

using namespace bebone::gfx;

const std::vector<Vec3f> vertices = { {-0.5f, -0.5f, 0.0f}, {0.5f, -0.5f, 0.0f}, {0.0f,  0.5f, 0.0f} };
const std::vector<u32> indices = { 0, 1, 2, };

int main() {
    auto window = WindowFactory::create_window("1. OpenGL hello triangle example", screen_width, screen_height, OpenGL);

    GLContext::load_opengl();
    GLContext::set_viewport(0, 0, screen_width, screen_height);

    GLShader vertex_shader = GLShaderFactory::create_shader("vertex.glsl", VertexShader);
    GLShader fragment_shader = GLShaderFactory::create_shader("fragment.glsl", FragmentShader);
    GLShaderProgram shader_program(vertex_shader, fragment_shader);

    vertex_shader.destroy();
    fragment_shader.destroy();
    
    GLVertexArrayObject vao;
    vao.bind();

    GLVertexBufferObject vbo(vertices.data(), vertices.size() * sizeof(Vec3f));
    GLElementBufferObject ebo(indices.data(), indices.size() * sizeof(u32));

    vao.link_attributes(vbo, 0, 3, GL_FLOAT, sizeof(Vec3f), nullptr);

    vao.unbind();
	vbo.unbind();
	ebo.unbind();

    GLContext::disable(GL_DEPTH_TEST);

    while(!window->closing()) {
        GLContext::clear_color(0.2f, 0.2f, 0.2f, 1.0f);
        GLContext::clear(GL_COLOR_BUFFER_BIT);

        shader_program.enable();
        vao.bind();
        GLContext::draw_arrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window->get_backend());
        window->pull_events();
    }

    vao.destroy();
    vbo.destroy();
    ebo.destroy();
    shader_program.destroy();

    return 0;
}

