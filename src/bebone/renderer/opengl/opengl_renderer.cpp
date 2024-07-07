#include "opengl_renderer.h"

namespace bebone::renderer {
    GLRenderer::GLRenderer(std::shared_ptr<Window>& window) : IRenderer(OpenGL) {

    }

    GLRenderer::~GLRenderer() {

    }

    SpriteHandle GLRenderer::load_sprite(const std::string& file_path) {

    };

    ModelHandle GLRenderer::load_model(const std::string& file_path) {

    };

    MeshHandle GLRenderer::create_mesh(const std::vector<Vertex>& vertices, const std::vector<u32>& indicies) {

    };


    void GLRenderer::render(const SpriteHandle& handle, const Transform& transform) {

    }

    void GLRenderer::render(const MeshHandle& handle, const Transform& transform) {

    }

    void GLRenderer::render(const ModelHandle& handle, const Transform& transform) {

    }

    void GLRenderer::present() {

    }
}
