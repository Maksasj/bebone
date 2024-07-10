#include "opengl_renderer.h"

namespace bebone::renderer {
    GLRenderer::GLRenderer(std::shared_ptr<Window>& window) : IRenderer(OpenGL), window(window) {
        GLContext::load_opengl();

        GLShader vertex_shader = GLShaderFactory::create_shader("vertex.glsl", VertexShader, GLShaderProperties::None);
        GLShader fragment_shader = GLShaderFactory::create_shader("fragment.glsl", FragmentShader, GLShaderProperties::None);

        shader_program = std::make_unique<GLShaderProgram>(vertex_shader, fragment_shader);

        vertex_shader.destroy();
        fragment_shader.destroy();
    }

    GLRenderer::~GLRenderer() {
        shader_program->destroy();
    }

    SpriteHandle GLRenderer::load_sprite(const std::string& file_path) {

    };

    ModelHandle GLRenderer::load_model(const std::string& file_path) {

    };

    MeshHandle GLRenderer::create_mesh(const std::vector<Vertex>& vertices, const std::vector<u32>& indices) {
        auto mesh = std::make_shared<OpenGLTriangleMesh>(vertices, indices);
        meshes_to_render.push_back(mesh);
        return { .index = meshes_to_render.size() - 1 };
    };

    void GLRenderer::render(const SpriteHandle& handle, const Transform& transform) {

    }

    void GLRenderer::render(const MeshHandle& handle, const Transform& transform) {
        auto mesh = meshes_to_render[handle.index];
        auto triangle = static_pointer_cast<OpenGLTriangleMesh>(mesh);
        triangle->bind(nullptr);
    }

    void GLRenderer::render(const ModelHandle& handle, const Transform& transform) {

    }

    void GLRenderer::present() {
        GLContext::clear_color(0.2f, 0.2f, 0.2f, 1.0f);
        GLContext::clear(GL_COLOR_BUFFER_BIT);

        shader_program->enable();
        auto mesh = meshes_to_render[0];
        GLContext::draw_elements(GL_TRIANGLES, static_cast<i32>(mesh->triangle_count()), GL_UNSIGNED_INT, nullptr);
        GLFWContext::poll_events();
        glfwSwapBuffers(window->get_backend());
    }

    std::shared_ptr<IRenderGraphImpl> GLRenderer::create_render_graph(const std::string& name) {

    }
}
