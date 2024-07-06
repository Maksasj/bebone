#include <vector>

#define BEBONE_TYPES_MATRIX_COLUMN_MAJOR_ORDER
#define BEBONE_TYPES_MATRIX4X4_PROJECTION_MATRIX_INVERSE_Y_AXIS
#include "bebone/bebone.h"

const unsigned int screen_width = 800;
const unsigned int screen_height = 600;

using namespace bebone::gfx;

struct Vertex {
    Vec3f pos;
    ColorRGBA color;
};

const std::vector<Vertex> vertices {
    {{-1.0, -1.0,  1.0},   ColorRGBA::WHITE  },
    {{ 1.0, -1.0,  1.0},   ColorRGBA::YELLOW },
    {{ 1.0,  1.0,  1.0},   ColorRGBA::MAGENTA},
    {{-1.0,  1.0,  1.0},   ColorRGBA::RED    },
    {{-1.0, -1.0, -1.0},   ColorRGBA::CYAN   },
    {{ 1.0, -1.0, -1.0},   ColorRGBA::GREEN  },
    {{ 1.0,  1.0, -1.0},   ColorRGBA::BLUE   },
    {{-1.0,  1.0, -1.0},   ColorRGBA::BLACK  }
};

const std::vector<u32> indices {
    0, 1, 2, 2, 3, 0,
    1, 5, 6, 6, 2, 1,
    7, 6, 5, 5, 4, 7,
    4, 0, 3, 3, 7, 4,
    4, 5, 1, 1, 0, 4,
    3, 2, 6, 6, 7, 3
};

struct Transform {
    Mat4f translation;
    Mat4f scale;
    Mat4f rotation;
};

struct Camera {
    Mat4f proj;
    Mat4f view;
};

int main() {
    glfwInit();

    auto window = WindowFactory::create_window("3. OpenGL 3D cube example", screen_width, screen_height, OpenGL);

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
    vao.link_attributes(vbo, 1, 4, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, color));

    vao.unbind();
	vbo.unbind();
	ebo.unbind();

    GLUniformBufferObject transform_ubo(sizeof(Transform));
    GLUniformBufferObject camera_ubo(sizeof(Camera));

    transform_ubo.bind();
    shader_program.bind_buffer("Transform", 0, transform_ubo);
    auto transform_ptr = static_cast<Transform*>(transform_ubo.map());
        transform_ptr->translation = Mat4f::translation(Vec3f::zero);
        transform_ptr->scale = Mat4f::identity();

    camera_ubo.bind();
    shader_program.bind_buffer("Camera", 1, camera_ubo);
    auto camera_ptr = static_cast<Camera*>(camera_ubo.map());
        camera_ptr->proj = Mat4f::perspective(1, window->get_aspect(), 0.1f, 100.0f);
        camera_ptr->view = Mat4f::translation(Vec3f(0, 0, 5));
    camera_ubo.unmap();
    camera_ubo.unbind();

    GLContext::enable(GL_DEPTH_TEST);

    f32 t = 0.0f;
    while (!window->closing()) {
        t += Time::get_delta_time();

        GLContext::clear_color(0.2f, 0.2f, 0.2f, 1.0f);
        GLContext::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        transform_ptr->rotation = trait_bryan_angle_yxz(Vec3f(t, t, 0.0f));

        shader_program.enable();

        vao.bind();

        GLContext::draw_elements(GL_TRIANGLES, static_cast<i32>(indices.size()), GL_UNSIGNED_INT, nullptr);

        GLFWContext::swap_buffers(*window);
        GLFWContext::poll_events();

        window->end_frame();
    }

    transform_ubo.unmap();
    transform_ubo.unbind();

    vao.destroy();
    vbo.destroy();
    ebo.destroy();
    shader_program.destroy();

    GLFWContext::terminate();

    return 0;
}
