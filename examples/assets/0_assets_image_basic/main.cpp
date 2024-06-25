#include "bebone/bebone.h"

#include <vector>

const unsigned int screen_width = 512;
const unsigned int screen_height = 512;

using namespace bebone::assets;
using namespace bebone::gfx;
using namespace bebone::gfx::opengl;

struct Vertex {
    Vec3f pos;
    Vec2f tex_coords;
};

const std::vector<Vertex> vertices {
    {{1.0f,  1.0f, 0.0f},  {1.0f, 1.0f}},
    {{1.0f, -1.0f, 0.0f},  {1.0f, 0.0f}},
    {{-1.0f, -1.0f, 0.0f}, {0.0f, 0.0f}},
    {{-1.0f,  1.0f, 0.0f}, {0.0f, 1.0f}}
};

const std::vector<u32> indices {
    0, 1, 3,
    1, 2, 3
};

int main() {
    GLFWContext::init();

    auto window = WindowFactory::create_window("0. Image example basic", screen_width, screen_height, GfxAPI::OpenGL);

    GLContext::load_opengl();
    GLContext::set_viewport(0, 0, screen_width, screen_height);

    auto vertex_shader = GLShaderFactory::create_shader("vertex.glsl", ShaderTypes::vertex_shader);
    auto fragment_shader = GLShaderFactory::create_shader("fragment.glsl", ShaderTypes::fragment_shader);
    GLShaderProgram shader_program(vertex_shader, fragment_shader);
    shader_program.set_uniform("ourTexture", 0);

    vertex_shader.destroy();
    fragment_shader.destroy();
    
    GLVertexArrayObject vao;
    vao.bind();

    GLVertexBufferObject vbo(vertices.data(), vertices.size() * sizeof(Vertex));
    GLElementBufferObject ebo(indices.data(), indices.size() * sizeof(u32));

    vao.link_attributes(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, pos));
    vao.link_attributes(vbo, 1, 2, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, tex_coords));

    vao.unbind();
	vbo.unbind();
	ebo.unbind();

    // auto image = Image<ColorRGBA>::from_color(512, 512, ColorRGBA::GREEN);
    // auto image = Image<ColorRGBA>::from_white_noise(512, 512);
    auto image = Image<ColorRGBA>::load_from_file("image.png");

    auto painter = ImagePainter<ColorRGBA>::from_image(image);

    auto texture = make_shared<GLTexture2D>(image);

    window->add_listener([&](InputMouseButtonEvent& event) {
        double x_pos, y_pos;
        glfwGetCursorPos(window->get_backend(), &x_pos, &y_pos);

        if(event.button == GLFW_MOUSE_BUTTON_LEFT) {
            painter.paint_circle(x_pos, y_pos, 20, ColorRGBA::RED);
            texture = make_shared<GLTexture2D>(image);
        } else if(event.button == GLFW_MOUSE_BUTTON_RIGHT) {
            painter.paint_square(x_pos, y_pos, 5, 5, ColorRGBA::BLUE);
            texture = make_shared<GLTexture2D>(image);
        }
    });

    window->add_listener([&](InputKeyEvent& event) {
        if(event.key == GLFW_KEY_ENTER && event.action == GLFW_RELEASE) {
            image->export_to_file("result.png");
        }
    });

    GLContext::enable(GL_CULL_FACE);
    GLContext::cull_face(GL_BACK);
    GLContext::front_face(GL_CW);

    while (!window->closing()) {
        GLContext::clear_color(0.2f, 0.2f, 0.2f, 1.0f);
        GLContext::clear(GL_COLOR_BUFFER_BIT);

        shader_program.enable();

        texture->bind();
        vao.bind();

        GLContext::draw_elements(GL_TRIANGLES, static_cast<i32>(indices.size()), GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(window->get_backend());
        GLFWContext::poll_events();
    }

    GLFWContext::terminate();

    return 0;
}
