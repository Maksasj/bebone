#ifndef _BEBONE_RENDERER_IRENDERER_H_
#define _BEBONE_RENDERER_IRENDERER_H_

#include "renderer_backend.h"

#include "irender_graph.h"
#include "ipass.h"

#include "imesh.h"
#include "imesh_builder.h"
#include "imesh_generator.h"
#include "imesh_loader.h"
#include "obj_mesh_loader.h"

#include "vertex.h"
#include "vertex_triangle.h"
#include "transform.h"

namespace bebone::renderer {
    struct MeshHandle { size_t index; };

    class IRenderer {
        private:
            const GfxAPI api;

        public:
            explicit IRenderer(const GfxAPI& api);

            virtual ~IRenderer() = default;

            virtual MeshHandle create_mesh(const std::vector<Vertex>& vertices, const std::vector<u32>& indicies) = 0;

            // Todo, implement
            virtual void render(const MeshHandle& handle, const Transform& transform) = 0;

            virtual void present() = 0;

            virtual std::shared_ptr<IRenderGraph> create_render_graph(const std::string& name) = 0;
    };
}

#endif
