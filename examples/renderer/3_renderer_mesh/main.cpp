#include <vector>

#define BEBONE_TYPES_MATRIX_COLUMN_MAJOR_ORDER
#define BEBONE_TYPES_MATRIX4X4_PROJECTION_MATRIX_INVERSE_Y_AXIS
#include "bebone/bebone.h"

using namespace bebone::gfx;
using namespace bebone::renderer;

struct Camera {
    Mat4f proj;
    Mat4f view;
};

int main() {
    glfwInit();

    auto window = WindowFactory::create_window("3. Renderer mesh", 800, 600, OpenGL);

    GLContext::load_opengl();
    GLContext::set_viewport(0, 0, 800, 600);

    auto vertex_shader = GLShaderFactory::create_shader("vertex.glsl", VertexShader);
    auto fragment_shader = GLShaderFactory::create_shader("fragment.glsl", FragmentShader);
    GLShaderProgram shader_program(vertex_shader, fragment_shader);

    vertex_shader.destroy();
    fragment_shader.destroy();

    GLUniformBufferObject transform_ubo(sizeof(Mat4f));
    GLUniformBufferObject camera_ubo(sizeof(Camera));

    Transform transform;

    transform_ubo.bind();
    shader_program.bind_buffer("Transform", 0, transform_ubo);
    auto transform_ptr = static_cast<Mat4f*>(transform_ubo.map());
    *transform_ptr = transform.final_matrix();

    camera_ubo.bind();
    shader_program.bind_buffer("Camera", 1, camera_ubo);
    auto camera_ptr = static_cast<Camera*>(camera_ubo.map());
    camera_ptr->proj = Mat4f::perspective(1, window->get_aspect(), 0.1f, 100.0f);
    camera_ptr->view = Mat4f::translation(Vec3f(0, 0, 5));
    camera_ubo.unmap();
    camera_ubo.unbind();

    GLContext::enable(GL_DEPTH_TEST);

    auto loader = std::make_shared<OBJMeshLoader>(std::make_shared<OpenGLTriangleMeshBuilder>());
    auto mesh = loader->load_from_file("suzanne.obj");

    f32 t = 0.0f;
    while (!window->closing()) {
        t += 0.01;

        transform.rotation.x = sin(t);
        transform.rotation.y = sin(t);

        *transform_ptr = transform.final_matrix();

        GLContext::clear_color(0.2f, 0.2f, 0.2f, 1.0f);
        GLContext::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader_program.enable();

        mesh->bind();
        GLContext::draw_elements(GL_TRIANGLES, static_cast<i32>(mesh->triangle_count()), GL_UNSIGNED_INT, nullptr);

        GLFWContext::swap_buffers(*window);
        GLFWContext::poll_events();
    }

    transform_ubo.unmap();
    transform_ubo.unbind();

    shader_program.destroy();

    GLFWContext::terminate();

    return 0;
}
