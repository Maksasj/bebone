#include <vector>

#define BEBONE_TYPES_MATRIX_COLUMN_MAJOR_ORDER
#define BEBONE_TYPES_MATRIX4X4_PROJECTION_MATRIX_INVERSE_Y_AXIS
#include "bebone/bebone.h"

const unsigned int screen_width = 800;
const unsigned int screen_height = 600;

using namespace bebone;
using namespace bebone::gfx;
using namespace bebone::renderer;
using namespace bebone::gfx::opengl;

class CubeMeshGenerator : public IMeshGenerator {
    public:
        CubeMeshGenerator(const std::shared_ptr<IMeshBuilder>& builder) : IMeshGenerator(builder) {

        }

        void reset() override {

        }

        std::shared_ptr<IMesh> generate() override {
            const vector<Vertex> vertices {
                {{-1.0, -1.0,  1.0},   {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
                {{ 1.0, -1.0,  1.0},   {1.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
                {{ 1.0,  1.0,  1.0},   {1.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
                {{-1.0,  1.0,  1.0},   {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
                {{-1.0, -1.0, -1.0},   {0.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
                {{ 1.0, -1.0, -1.0},   {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
                {{ 1.0,  1.0, -1.0},   {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
                {{-1.0,  1.0, -1.0},   {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}}
            };

            const vector<u32> indices {
                    0, 1, 2, 2, 3, 0,
                    1, 5, 6, 6, 2, 1,
                    7, 6, 5, 5, 4, 7,
                    4, 0, 3, 3, 7, 4,
                    4, 5, 1, 1, 0, 4,
                    3, 2, 6, 6, 7, 3
            };

            return std::make_shared<OpenGLTriangleMesh>(vertices, indices);
        }
};

int main() {
    glfwInit();

    auto window = WindowFactory::create_window("7. OpenGL bloom example", screen_width, screen_height, GfxAPI::OpenGL);

    GLContext::load_opengl();
    GLContext::set_viewport(0, 0, screen_width, screen_height);

    auto vertex_shader = GLShaderFactory::create_shader("vertex.glsl", ShaderTypes::vertex_shader, EnableUniforms);
    auto fragment_shader = GLShaderFactory::create_shader("fragment.glsl", ShaderTypes::fragment_shader, EnableUniforms);
    GLShaderProgram shader_program(vertex_shader, fragment_shader);
    vertex_shader.destroy();
    fragment_shader.destroy();

    GLContext::enable(GL_DEPTH_TEST);

    auto transform = renderer::Transform {};
    auto camera = Mat4f::translation(Vec3f(0, 0, 5)) * Mat4f::perspective(1, window->get_aspect(), 0.1f, 100.0f);

    auto generator = std::make_shared<CubeMeshGenerator>(std::make_shared<OpenGLTriangleMeshBuilder>());
    auto mesh = generator->generate();

    while (!window->closing()) {
        GLContext::clear_color(0.2f, 0.2f, 0.2f, 1.0f);
        GLContext::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        transform.rotation.x += 0.1f;
        transform.rotation.z -= 0.1f;

        shader_program.enable();

        shader_program.set_uniform("transform", transform.final_matrix());
        shader_program.set_uniform("cam", camera);

        mesh->bind();
        GLContext::draw_elements(GL_TRIANGLES, static_cast<i32>(mesh->triangle_count()), GL_UNSIGNED_INT, nullptr);

        GLFWContext::swap_buffers(*window);
        GLFWContext::poll_events();
    }

    shader_program.destroy();

    GLFWContext::terminate();

    return 0;
}
