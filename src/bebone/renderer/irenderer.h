#ifndef _BEBONE_RENDERER_IRENDERER_H_
#define _BEBONE_RENDERER_IRENDERER_H_

#include "renderer_backend.h"

#include "irender_graph.h"
#include "ipass.h"

#include "imaterial.h"

#include "imesh.h"
#include "imesh_builder.h"
#include "imesh_generator.h"
#include "imesh_loader.h"
#include "obj_mesh_loader.h"

#include "vertex.h"
#include "transform.h"

#include "pbr_render_graph.h"

namespace bebone::renderer {
    struct MeshHandle { size_t index; };

    class IRenderer {
        private:
            const GfxAPI api;

        protected:
            virtual void resize_viewport(const Vec2i& new_size) = 0;

            std::shared_ptr<IRenderGraph> create_default_render_graph();

        public:
            IRenderer(const GfxAPI& api);
            virtual ~IRenderer() = default;

            virtual MeshHandle load_mesh(const std::string& file_path) = 0;
            virtual MeshHandle create_mesh(const std::vector<Vertex>& vertices, const std::vector<u32>& indicies) = 0;

            virtual void render(const MeshHandle& handle, const Transform& transform) = 0;

            virtual void present() = 0;

            virtual std::shared_ptr<IRenderGraphImpl> create_render_graph_impl() = 0;
            std::shared_ptr<IRenderGraph> create_render_graph(const std::string& name);

            const GfxAPI& get_api() const;
    };
}

#endif
