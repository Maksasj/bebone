#include <vector>
#include "bebone/bebone.h"

const unsigned int screen_width = 800;
const unsigned int screen_height = 600;

using namespace bebone::gfx;

struct Vertex {
    Vec3f pos;
    ColorRGBA color;
};

const vector<Vertex> vertices {
    {{ -1.0, -1.0, 1.0 }, ColorRGBA::WHITE  },
    {{ 1.0, -1.0, 1.0 }, ColorRGBA::YELLOW },
    {{ 1.0, 1.0, 1.0 }, ColorRGBA::MAGENTA},
    {{ -1.0, 1.0, 1.0 }, ColorRGBA::RED    },
    {{ -1.0, -1.0, -1.0 }, ColorRGBA::CYAN   },
    {{ 1.0, -1.0, -1.0 }, ColorRGBA::GREEN  },
    {{ 1.0, 1.0, -1.0 }, ColorRGBA::BLUE   },
    {{ -1.0, 1.0, -1.0 }, ColorRGBA::BLACK  }
};

const vector<u32> indices {
    0, 1, 2, 2, 3, 0, 1, 5, 6, 6, 2, 1, 7, 6, 5, 5, 4, 7, 4, 0, 3, 3, 7, 4, 4, 5, 1, 1, 0, 4, 3, 2, 6, 6, 7, 3
};

struct Transform {
    Mat4f translation;
    Mat4f rotation;
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

    GLUniformBufferObject transform_ubo(sizeof(Mat4f));
    GLUniformBufferObject camera_ubo(sizeof(Mat4f));

    auto transform = Transform {};
    transform.translation = Mat4f::translation(Vec3f(0.0f, 0.0f, 10.0f));
    transform.rotation = Mat4f::identity();

    transform_ubo.bind();
    shader_program.bind_buffer("Transform", 0, transform_ubo);
    auto transform_ptr = static_cast<Mat4f*>(transform_ubo.map());
        *transform_ptr = transform.translation * transform.rotation;

    camera_ubo.bind();
    shader_program.bind_buffer("Camera", 1, camera_ubo);
    auto camera_ptr = static_cast<Mat4f*>(camera_ubo.map());
        *camera_ptr = Mat4f::perspective(1, window->get_aspect(), 0.1f, 100.0f) *  Mat4f::look_at(Vec3f(0, 0, -10.0f), Vec3f(0.0f, 0.0f, 0.0f), Vec3f::up);
    camera_ubo.unmap();
    camera_ubo.unbind();

    while (!window->closing()) {
        GLContext::clear_color(0.2f, 0.2f, 0.2f, 1.0f);
        GLContext::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        const auto t = static_cast<f32>(Time::get_seconds_elapsed());
        transform.rotation = trait_bryan_angle_yxz(Vec3f(t, t, 0.0f));
        *transform_ptr = transform.translation * transform.rotation;

        auto time = Time::get_seconds_elapsed();
        auto pos = Vec3f((sin(time)) * 5.0f, 0.0f, (sin(time)) * 5.0f);
        transform.translation = Mat4f::translation(pos);

        shader_program.enable();
        vao.bind();

        GLContext::draw_elements(GL_TRIANGLES, static_cast<i32>(indices.size()), GL_UNSIGNED_INT, nullptr);

        GLFWContext::swap_buffers(*window);
        window->pull_events();
    }

    transform_ubo.unmap();
    transform_ubo.unbind();

    vao.destroy();
    vbo.destroy();
    ebo.destroy();
    shader_program.destroy();

    return 0;
}
