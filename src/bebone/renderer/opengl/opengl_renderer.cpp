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

    void GLRenderer::resize_viewport(const Vec2i& new_size) {
        // Todo
    }

    TextureHandle GLRenderer::load_texture(const std::string& file_path) {

    }

    std::shared_ptr<IMesh> GLRenderer::load_mesh(const std::string& file_path) {
        // auto loader = std::make_shared<OBJMeshLoader>(std::make_shared<OpenGLTriangleMeshBuilder>());
        // auto mesh = loader->load_from_file(file_path);
        // meshes_to_render.push_back(mesh);
        // return { meshes_to_render.size() - 1 };
    }

    std::shared_ptr<IMesh> GLRenderer::create_mesh(const std::vector<Vertex>& vertices, const std::vector<u32>& indices) {
        // auto mesh = std::make_shared<OpenGLTriangleMesh>(vertices, indices);
        // meshes_to_render.push_back(mesh);
        // return { .index = meshes_to_render.size() - 1 };
    };

    void GLRenderer::render(const ModelHandle& handle, const Transform& transform) {
        std::ignore = transform;
        auto mesh = meshes_to_render[handle.index];
        auto triangle = static_pointer_cast<OpenGLTriangleMesh>(mesh);
        triangle->bind(nullptr);
    }

    void GLRenderer::present() {
        GLContext::clear_color(0.2f, 0.2f, 0.2f, 1.0f);
        GLContext::clear(GL_COLOR_BUFFER_BIT);

        shader_program->enable();
        auto mesh = meshes_to_render[0];
        GLContext::draw_elements(GL_TRIANGLES, static_cast<i32>(mesh->triangle_count()), GL_UNSIGNED_INT, nullptr);
        glfwSwapBuffers(window->get_backend());
    }

    std::shared_ptr<IRenderGraphImpl> GLRenderer::create_render_graph_impl() {
        // Todo
    }
}
