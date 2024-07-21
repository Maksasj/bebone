#include "bebone/bebone.h"

#include <vector>

const unsigned int screen_width = 800;
const unsigned int screen_height = 600;

using namespace bebone::gfx;

struct Vertex {
    Vec3f pos;
    Vec3f color;
    Vec2f tex_coords;
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

    auto window = WindowFactory::create_window("2. OpenGL texture example", screen_width, screen_height, OpenGL);

    GLContext::load_opengl();
    GLContext::set_viewport(0, 0, screen_width, screen_height);

    auto vertex_shader = GLShaderFactory::create_shader("vertex.glsl", VertexShader);
    auto fragment_shader = GLShaderFactory::create_shader("fragment.glsl", FragmentShader);
    GLShaderProgram shader_program(vertex_shader, fragment_shader);

    vertex_shader.destroy();
    fragment_shader.destroy();
    
    GLVertexArrayObject vao;
    vao.bind();

    GLVertexBufferObject vbo(vertices.data(), vertices.size() * sizeof(Vertex));
    GLElementBufferObject ebo(indices.data(), indices.size() * sizeof(u32));

    vao.link_attributes(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, pos));
    vao.link_attributes(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, color));
    vao.link_attributes(vbo, 2, 2, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, tex_coords));

    vao.unbind();
	vbo.unbind();
	ebo.unbind();

    GLTexture2D texture("image.png");

    shader_program.set_uniform("ourTexture", 0);

    while (!window->closing()) {
        GLContext::clear_color(0.2f, 0.2f, 0.2f, 1.0f);
        GLContext::clear(GL_COLOR_BUFFER_BIT);

        shader_program.enable();

        texture.bind();
        vao.bind();

        GLContext::draw_elements(GL_TRIANGLES, static_cast<i32>(indices.size()), GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(window->get_backend());
        window->pull_events();
    }

    GLFWContext::terminate();

    return 0;
}
