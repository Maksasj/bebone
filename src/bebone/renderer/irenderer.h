#ifndef _BEBONE_RENDERER_IRENDERER_H_
#define _BEBONE_RENDERER_IRENDERER_H_

#include "renderer_backend.h"

#include "mesh/imesh.h"
#include "mesh/imesh_builder.h"
#include "mesh/imesh_generator.h"
#include "mesh/imesh_loader.h"
#include "mesh/obj_mesh_loader.h"

#include "vertex.h"
#include "vertex_triangle.h"
#include "transform.h"

namespace bebone::renderer {
    class IRenderer;

    // class IBindable {}; // ?
    // Abstract classes
    class IProgram {}; // This is shader
    // class IRenderPass;

    class IUniformBuffer {};
    class IVertexBuffer {};
    class IIndexBuffer {};
    class ITexture {};

    // class IMesh {};
    class IMaterial {};

    class ISprite {};
    class IModel {};

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

    // Helper classes
    // struct Vertex {};

    class RendererFactory;

    class IRenderer {
        private:
            const GfxAPI api;

        public:
            explicit IRenderer(const GfxAPI& api);

            virtual ~IRenderer() = default;

            // Todo, implement
            virtual SpriteHandle load_sprite(const std::string& file_path) {};
            virtual ModelHandle load_model(const std::string& file_path) {};

            virtual MeshHandle create_mesh(const std::vector<Vertex>& vertices, const std::vector<u32>& indicies) = 0;

            // Todo, implement
            virtual void render(const SpriteHandle&, const Transform&) {};
            virtual void render(const MeshHandle&, const Transform&) {};
            virtual void render(const ModelHandle&, const Transform&) {};

            virtual void present() = 0;
    };
}

#endif
