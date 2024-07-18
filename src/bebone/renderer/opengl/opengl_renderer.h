#ifndef _BEBONE_RENDERER_OPENGL_RENDERER_H_
#define _BEBONE_RENDERER_OPENGL_RENDERER_H_

#include "../irenderer.h"

#include "opengl_triangle_mesh.h"
#include "opengl_triangle_mesh_builder.h"

namespace bebone::renderer {
    class GLRenderer : public IRenderer {
        private:
            std::shared_ptr<Window> window;

            std::unique_ptr<GLShaderProgram> shader_program;
            std::vector<std::shared_ptr<IMesh>> meshes_to_render;

        protected:
            void resize_viewport(const Vec2i& new_size) override;

        public:
            GLRenderer(std::shared_ptr<Window>& window);

            TextureHandle load_texture(const std::string& file_path) override;

            std::shared_ptr<IMesh> load_mesh(const std::string& file_path) override;
            std::shared_ptr<IMesh> create_mesh(const std::vector<Vertex>& vertices, const std::vector<u32>& indices) override;

            void render(const ModelHandle& handle, const Transform& transform = {}) override;

            void present() override;

            std::shared_ptr<IRenderGraphImpl> create_render_graph_impl() override;
    };
}

#endif
