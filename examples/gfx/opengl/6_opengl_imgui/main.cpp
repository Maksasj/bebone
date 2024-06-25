#include <vector>

#define BEBONE_TYPES_MATRIX_COLUMN_MAJOR_ORDER
#define BEBONE_TYPES_MATRIX4X4_PROJECTION_MATRIX_INVERSE_Y_AXIS
#include "bebone/bebone.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

using namespace bebone::gfx;
using namespace bebone::gfx::opengl;

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
    GLFWContext::init();

    auto window = WindowFactory::create_window("6. OpenGL Imgui example", SCR_WIDTH, SCR_HEIGHT, GfxAPI::OpenGL);

    GLContext::load_opengl();
    GLContext::set_viewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    glfwSwapInterval(0);

    auto vertexShader = GLShaderFactory::create_shader("vertex.glsl", ShaderTypes::VERTEX_SHADER);
    auto fragmentShader = GLShaderFactory::create_shader("fragment.glsl", ShaderTypes::FRAGMENT_SHADER);
    GLShaderProgram shaderProgram(vertexShader, fragmentShader);

    vertexShader.destroy();
    fragmentShader.destroy();
    
    GLVertexArrayObject vao;
    vao.bind();

    GLVertexBufferObject vbo(vertices.data(), sizeof(Vertex) * vertices.size());
    GLElementBufferObject ebo(indices.data(), indices.size() * sizeof(u32));

    vao.link_attributes(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, pos));
    vao.link_attributes(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, color));

    vao.unbind();
	vbo.unbind();
	ebo.unbind();

    GLUniformBufferObject transformUbo(sizeof(Transform));
    GLUniformBufferObject cameraUbo(sizeof(Camera));

    transformUbo.bind();
    shaderProgram.bind_buffer("Transform", 0, transformUbo);
    auto transformPtr = static_cast<Transform*>(transformUbo.map());
        transformPtr->translation = Mat4f::translation(Vec3f(0, 0, 0));
        transformPtr->scale = Mat4f::identity();

    cameraUbo.bind();
    shaderProgram.bind_buffer("Camera", 1, cameraUbo);
    auto cameraPtr = static_cast<Camera*>(cameraUbo.map());
        cameraPtr->proj = Mat4f::perspective(1, window->get_aspect(), 0.1f, 100.0f);
        cameraPtr->view = Mat4f::translation(Vec3f(0, 0, 5));
    cameraUbo.unmap();
    cameraUbo.unbind();

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

        transformPtr->rotation = trait_bryan_angle_yxz(Vec3f(t * 0.001f, t * 0.001f, 0.0f));

        shaderProgram.enable();

        vao.bind();

        GLContext::draw_elements(GL_TRIANGLES, static_cast<i32>(indices.size()), GL_UNSIGNED_INT, nullptr);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window->get_backend());
        GLFWContext::poll_events();
    }

    transformUbo.unmap();
    transformUbo.unbind();

    vao.destroy();
    vbo.destroy();
    ebo.destroy();
    shaderProgram.destroy();

    GLFWContext::terminate();

    return 0;
}
