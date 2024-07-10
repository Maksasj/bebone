#ifndef _BEBONE_RENDERER_IRENDERER_H_
#define _BEBONE_RENDERER_IRENDERER_H_

#include "renderer_backend.h"

#include "irender_graph_impl.h"
#include "ipass.h"

#include "iprogram.h"
#include "itexture.h"
#include "iindex_buffer.h"
#include "ivertex_buffer.h"
#include "iuniform_buffer.h"

#include "imaterial.h"
#include "isprite.h"
#include "imodel.h"

#include "mesh/imesh.h"
#include "mesh/imesh_builder.h"
#include "mesh/imesh_generator.h"
#include "mesh/imesh_loader.h"
#include "mesh/obj_mesh_loader.h"

#include "vertex.h"
#include "vertex_triangle.h"
#include "transform.h"

namespace bebone::renderer {
    // Handle types
    struct ProgramHandle { size_t index; };
    struct UniformBufferHandle { size_t index; };
    struct VertexBufferHandle { size_t index; };
    struct IndexBufferHandle { size_t index; };
    struct TextureHandle { size_t index; };

    struct MeshHandle { size_t index; };
    struct MaterialHandle { size_t index; };
    struct SpriteHandle { size_t index; };
    struct ModelHandle { size_t index; };

    class IRenderer {
        private:
            const GfxAPI api;

        public:
            explicit IRenderer(const GfxAPI& api);

            virtual ~IRenderer() = default;

            // Todo, implement
            virtual SpriteHandle load_sprite(const std::string& file_path) = 0;
            virtual ModelHandle load_model(const std::string& file_path) = 0;

            virtual MeshHandle create_mesh(const std::vector<Vertex>& vertices, const std::vector<u32>& indicies) = 0;

            // Todo, implement
            virtual void render(const SpriteHandle& handle, const Transform& transform) = 0;
            virtual void render(const MeshHandle& handle, const Transform& transform) = 0;
            virtual void render(const ModelHandle& handle, const Transform& transform) = 0;

            virtual void present() = 0;

            virtual std::shared_ptr<IRenderGraphImpl> create_render_graph(const std::string& name) = 0;
    };
}

#endif
