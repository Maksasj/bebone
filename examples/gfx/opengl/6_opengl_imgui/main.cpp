#include <vector>

#include "bebone/bebone.h"

const unsigned int screen_width = 800;
const unsigned int screen_height = 600;

using namespace bebone::gfx;

struct Vertex {
    Vec3f pos;
    Vec3f color;
};

const std::vector<Vertex> vertices {
    {{-0.5, -0.5,  0.5},   {1.0f, 1.0f, 1.0f}},
    {{ 0.5, -0.5,  0.5},   {1.0f, 1.0f, 0.0f}},
    {{ 0.5,  0.5,  0.5},   {1.0f, 0.0f, 1.0f}},
    {{-0.5,  0.5,  0.5},   {1.0f, 0.0f, 0.0f}},
    {{-0.5, -0.5, -0.5},   {0.0f, 1.0f, 1.0f}},
    {{ 0.5, -0.5, -0.5},   {0.0f, 1.0f, 0.0f}},
    {{ 0.5,  0.5, -0.5},   {0.0f, 0.0f, 1.0f}},
    {{-0.5,  0.5, -0.5},   {0.0f, 0.0f, 0.0f}}
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
    auto window = WindowFactory::create_window("6. OpenGL Imgui example", screen_width, screen_height, OpenGL);

    GLContext::load_opengl();
    GLContext::set_viewport(0, 0, screen_width, screen_height);
    glfwSwapInterval(0);

    auto vertex_shader = GLShaderFactory::create_shader("vertex.glsl", VertexShader);
    auto fragment_shader = GLShaderFactory::create_shader("fragment.glsl", FragmentShader);
    GLShaderProgram shader_program(vertex_shader, fragment_shader);

    vertex_shader.destroy();
    fragment_shader.destroy();
    
    GLVertexArrayObject vao;
    vao.bind();

    GLVertexBufferObject vbo(vertices.data(), sizeof(Vertex) * vertices.size());
    GLElementBufferObject ebo(indices.data(), indices.size() * sizeof(u32));

    vao.link_attributes(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, pos));
    vao.link_attributes(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, color));

    vao.unbind();
	vbo.unbind();
	ebo.unbind();

    GLUniformBufferObject transform_ubo(sizeof(Transform));
    GLUniformBufferObject camera_ubo(sizeof(Camera));

    transform_ubo.bind();
    shader_program.bind_buffer("Transform", 0, transform_ubo);
    auto transform_ptr = static_cast<Transform*>(transform_ubo.map());
        transform_ptr->translation = Mat4f::translation(Vec3f(0, 0, 0));
        transform_ptr->scale = Mat4f::identity();

    camera_ubo.bind();
    shader_program.bind_buffer("Camera", 1, camera_ubo);
    auto camera_ptr = static_cast<Camera*>(camera_ubo.map());
        camera_ptr->proj = Mat4f::perspective(1, window->get_aspect(), 0.1f, 100.0f);
        camera_ptr->view = Mat4f::translation(Vec3f(0, 0, 5));
    camera_ubo.unmap();
    camera_ubo.unbind();

    float t = 0;

    GLContext::enable(GL_DEPTH_TEST);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_None;

    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window->get_backend(), true);
    ImGui_ImplOpenGL3_Init("#version 330");

    while (!window->closing()) {
        ++t;

        GLContext::clear_color(0.2f, 0.2f, 0.2f, 1.0f);
        GLContext::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::ShowDemoWindow();

        transform_ptr->rotation = trait_bryan_angle_yxz(Vec3f(t * 0.001f, t * 0.001f, 0.0f));

        shader_program.enable();

        vao.bind();

        GLContext::draw_elements(GL_TRIANGLES, static_cast<i32>(indices.size()), GL_UNSIGNED_INT, nullptr);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window->get_backend());
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
