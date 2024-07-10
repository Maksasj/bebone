#ifndef _BEBONE_RENDERER_OPENGL_RENDERER_H_
#define _BEBONE_RENDERER_OPENGL_RENDERER_H_

#include "../irenderer.h"

#include "opengl_triangle_mesh.h"
#include "opengl_triangle_mesh_builder.h"

namespace bebone::renderer {
    class GLRenderer : public IRenderer {
        private:

        public:
            GLRenderer(std::shared_ptr<Window>& window);
            ~GLRenderer() override;

            SpriteHandle load_sprite(const std::string& file_path) override;
            ModelHandle load_model(const std::string& file_path) override;
            MeshHandle create_mesh(const std::vector<Vertex>& vertices, const std::vector<u32>& indicies) override;

            void render(const SpriteHandle& handle, const Transform& transform = {}) override;
            void render(const MeshHandle& handle, const Transform& transform = {}) override;
            void render(const ModelHandle& handle, const Transform& transform = {}) override;

            void present() override;

            std::shared_ptr<IRenderGraph> create_render_graph(const std::string& name) override;
    };
}

#endif
